
#include "coevent.h"
#include "cpp_tools.h"
#include "srv_log.h"
#include "srv_cgi.h"
#include "rapidjson_tools.h"

#include <stdio.h>
#include <string>

#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <arpa/inet.h>

using namespace andrewmc::libcoevent;
using namespace andrewmc::cpptools;
using namespace andrewmc::messager::server;

#define _CGI_PORT       (23333)

// ==========
#define __CGI_DEFINITIONS
#ifdef __CGI_DEFINITIONS

typedef void (*CgiProcessor)(TCPServer *, std::map<std::string, std::string> &, std::map<std::string, std::string> &, rapidjson::Document &, andrewmc::cpptools::Data &);
static std::map<std::string, CgiProcessor> g_cgi_processors;


static void _init_cgi_processors()
{
    g_cgi_processors["/cgi-bin/test"] = cgi::test::process;
    return;
}


#endif

// ==========
#define __COROUTINE_ENTRY
#ifdef __COROUTINE_ENTRY

static void _parse_url_para(std::map<std::string, std::string> &url_para, const char *para)
{
    if (NULL == para) {
        return;
    }

    // TODO:
    return;
}


static void _cgi_session(evutil_socket_t fd, Event *event, void *arg)
{
    TCPSession &session = *((TCPSession *)event);
    std::map<std::string, std::string> session_para;
    std::map<std::string, std::string> url_para;
    ::andrewmc::cpptools::Data data_buff;
    ::andrewmc::cpptools::Data data_body;
    struct Error status;
    size_t data_len = 0;
    TCPServer *server = (TCPServer *)arg;
    int port = server->port();

    data_buff.ensure_buff_capacity(10240);
    log::INFO("Server port: %d", port);
    log::INFO("Remote client address: %s:%u", session.remote_addr().c_str(), session.remote_port());

    // recv data
    status = session.recv(data_buff.mutable_raw_data(), data_buff.buff_capacity(), &data_len, 10.0);
    if (status.is_timeout()) {
        log::INFO("Session timeout");
        return;
    }

    // dump request data
    data_buff.set_raw_data_length(data_len);
    data_buff.append_nul();
    log::DEBUG("Got request:\n%s", andrewmc::cpptools::dump_data_to_string(data_buff).c_str());

    // parse data
    {
        std::vector<std::string> req_lines = ::andrewmc::cpptools::split_string(std::string((char *)data_buff.c_data()), "\r\n");

        if (req_lines.size() <= 5) {
            log::ERROR("insuffisent lines");
            return;
        }
        log::DEBUG("parameters count: %d", req_lines.size());

        // method
        {
            std::vector<std::string> method = ::andrewmc::cpptools::split_string(req_lines[0], " ");
            if (method.size() < 3) {
                log::INFO("Method line illegal");
                return;
            }
            log::INFO("Method: %s", method[0].c_str());
            log::INFO("URL: %s", method[1].c_str());
            log::INFO("Ver: %s", method[2].c_str());

            session_para["Method"] = method[0];
            session_para["URL"] = method[1];
        }

        // header parameters
        for (unsigned index = 1; index < req_lines.size(); ++index)
        {
            std::vector<std::string> parts = ::andrewmc::cpptools::split_string(req_lines[index], ": ");
            if (parts.size() < 2) {
                parts = ::andrewmc::cpptools::split_string(req_lines[index], ":");;
            }
            if (parts.size() < 2) {
                continue;
            }
            log::INFO("Param - '%s' : '%s'", parts[0].c_str(), parts[1].c_str());
            session_para[parts[0]] = parts[1];
        }

        // body parameters
        if (session_para["Method"] == "POST")
        {
            char *data_start = strstr((char *)data_buff.mutable_raw_data(), "\r\n\r\n");
            if (data_start) {
                size_t header_len = (size_t)(data_start - (char *)data_buff.c_data());
                data_body.copy(data_start + 4, data_buff.length() - header_len - 4);
            }
        }
    }

    // handle data
    {
        char str_buff[1024] = "";
        rapidjson::Document resp;
        data_buff.clear();
        std::string full_url = session_para["URL"];
        std::string url = "";

        // check URL parameters
        {
            int para_start = full_url.find('?');
            if ((int)std::string::npos != para_start)
            {
                url.assign(full_url, 0, para_start);
                _parse_url_para(url_para, full_url.substr(para_start + 1, std::string::npos).c_str());
                log::DEBUG("URL '%s', parameters '%s'", url.c_str(), full_url.substr(para_start + 1, std::string::npos).c_str());
            }
            else {
                url = full_url;
            }
        }

        tools::json_init(resp);
        
        // find handler
        std::map<std::string, CgiProcessor>::iterator handler = g_cgi_processors.find(url);
        if (handler != g_cgi_processors.end())
        {
            handler->second(server, session_para, url_para, resp, data_body);
            data_len = sprintf(str_buff, "HTTP/1.1 200 OK\r\nContent-type:application/json\r\n\r\n");
            data_buff.append(str_buff, data_len);
        }
        else
        {
            log::ERROR("Unrecognized URL: %s", full_url.c_str());
            data_len = sprintf(str_buff, "HTTP/1.1 404 Not Found\r\nContent-type:application/json\r\n\r\n");
            data_buff.append(str_buff, data_len);
        }

        // append body
        {
            std::string jsonStr = tools::json_dump(resp);
            size_t len = jsonStr.length();

            data_buff.append(jsonStr.c_str(), len);

            const char tail_str[] = "\r\n\r\n";
            data_buff.append(tail_str, sizeof(tail_str) - 1);
        }

        // reply
        session.reply(data_buff.c_data(), data_buff.length(), &data_len);
        log::DEBUG("Reply data: %s", andrewmc::cpptools::dump_data_to_string(data_buff).c_str());
        //log::INFO("Reply %u bytes", (unsigned)data_len);
    }

    // end
    log::INFO("Session ends");
    return;
}


#endif


// ==========
#define __MAIN
#ifdef __MAIN

int main(int argc, char *argv[])
{
    Base *base = new Base;
    Error status;
    TCPServer *server = new TCPServer;
    unsigned port = _CGI_PORT;

    if (argc > 1)
    {
        port = (unsigned)strtol(argv[1], NULL, 10);

        if (!(port > 0 && port < 65536)) {
            port = _CGI_PORT;
        }
    }
    log::INFO("CGI port %u", port);

    _init_cgi_processors();

    status = server->init_session_mode(base, _cgi_session, NetIPv4, port, server);
    if (FALSE == status.is_ok()) {
        log::INFO("Init CGI server failed: %s", status.c_err_msg());
        goto END;
    }

    base->run();

END:
    log::INFO("CGI server base ends");
    delete base;
    base = NULL;
    server = NULL;
    return 0;
}

#endif  // end of libcoevent::Base

