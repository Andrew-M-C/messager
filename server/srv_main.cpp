
#include "coevent.h"
#include "cpp_tools.h"
#include "srv_log.h"
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
#define __COROUTINE_ENTRY
#ifdef __COROUTINE_ENTRY

static void _cgi_session(evutil_socket_t fd, Event *event, void *arg)
{
    TCPSession &session = *((TCPSession *)event);
    std::map<std::string, std::string> req_para;
    ::andrewmc::cpptools::Data data_buff;
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
    log::DEBUG("Got request:\n(START)\n%s\n(ENDS)\n", (const char *)data_buff.c_data());

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

            req_para["URL"] = method[1];
        }

        // parameters
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
            req_para[parts[0]] = parts[1];
        }
    }

    // return data
    {
        char str_buff[1024] = "";
        data_buff.clear();

        // header
        data_len = sprintf(str_buff, "HTTP/1.1 200 OK\r\nContent-type:application/json\r\n\r\n");
        data_buff.append(str_buff, data_len);

        // body
        rapidjson::Document resp;
        tools::json_init(resp);

        // server time
        {
            time_t currSec = time(0);
            struct tm currTime;
            struct tm *pTime = localtime(&currSec);

            if (pTime)
            {
                memcpy(&currTime, pTime, sizeof(currTime));
                data_len = sprintf(str_buff, "%04d-%02d-%02d, %02d:%02d:%02d", 
                                    currTime.tm_year + 1900, currTime.tm_mon + 1, currTime.tm_mday,
                                    currTime.tm_hour, currTime.tm_min, currTime.tm_sec);
                tools::json_add_string(resp, "server time", str_buff);
            }
        }

        // client infos
        {
            std::map<std::string, std::string>::iterator iter_addr = req_para.find("X-Real-IP");
            std::map<std::string, std::string>::iterator iter_port = req_para.find("X-Real-Port");
            if (iter_addr != req_para.end() && iter_port != req_para.end()) {
                data_len = sprintf(str_buff, "%s:%s", iter_addr->second.c_str(), iter_port->second.c_str());
                tools::json_add_string(resp, "server client", str_buff);
            }
        }

        // server infos
        {
            std::map<std::string, std::string>::iterator iter_host = req_para.find("Host");
            std::map<std::string, std::string>::iterator iter_cgi = req_para.find("URL");
            if (iter_host != req_para.end() && iter_cgi != req_para.end()) {
                data_len = sprintf(str_buff, "https://%s%s", iter_host->second.c_str(), iter_cgi->second.c_str());
                tools::json_add_string(resp, "URL", str_buff);
            }
        }

        // User-Agent
        {
            std::map<std::string, std::string>::iterator iter_agent = req_para.find("User-Agent");
            if (iter_agent != req_para.end()) {
                tools::json_add_string(resp, "User-Agent", iter_agent->second.c_str());
            }
        }

        // server port
        {
            tools::json_add_uint32(resp, "server ID", port);
        }

        // append
        {
            std::string jsonStr = tools::json_dump(resp);
            size_t len = jsonStr.length();

            data_buff.append(jsonStr.c_str(), len);

            const char tail_str[] = "\r\n\r\n";
            data_buff.append(tail_str, sizeof(tail_str) - 1);
        }

        // reply
        session.reply(data_buff.c_data(), data_buff.length(), &data_len);
        log::INFO("Reply %u bytes", (unsigned)data_len);
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

