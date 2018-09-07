
#include "coevent.h"
#include "cpp_tools.h"
#include "srv_log.h"
#include "srv_cgi.h"
#include "cpptools_json.h"

#include <stdio.h>
#include <string>

#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <arpa/inet.h>

using namespace andrewmc;

// ==========
#define __PUBLIC_FUNCTIONS
#ifdef __PUBLIC_FUNCTIONS

void andrewmc::messager::server::cgi::test::process(andrewmc::libcoevent::TCPServer *server, 
                                                std::map<std::string, std::string> &session_para, 
                                                std::map<std::string, std::string> &req_para, 
                                                rapidjson::Document &resp, 
                                                andrewmc::cpptools::Data &post_data)
{
    int port = server->port();
    char str_buff[1024] = "";
    resp.SetObject();

    log::DEBUG("Got data body:\n%s", andrewmc::cpptools::dump_data_to_string(post_data).c_str());

    // server time
    {
        time_t currSec = time(0);
        struct tm currTime;
        struct tm *pTime = localtime(&currSec);

        if (pTime)
        {
            memcpy(&currTime, pTime, sizeof(currTime));
            sprintf(str_buff, "%04d-%02d-%02d, %02d:%02d:%02d", 
                    currTime.tm_year + 1900, currTime.tm_mon + 1, currTime.tm_mday,
                    currTime.tm_hour, currTime.tm_min, currTime.tm_sec);
            cpptools::json::add_string(resp, "server time", str_buff);
        }
    }

    // client infos
    {
        std::map<std::string, std::string>::iterator iter_addr = session_para.find("X-Real-IP");
        std::map<std::string, std::string>::iterator iter_port = session_para.find("X-Real-Port");
        if (iter_addr != session_para.end() && iter_port != session_para.end())
        {
            sprintf(str_buff, "%s:%s", iter_addr->second.c_str(), iter_port->second.c_str());
            cpptools::json::add_string(resp, "server client", str_buff);
        }
    }

    // server infos
    {
        std::map<std::string, std::string>::iterator iter_host = session_para.find("Host");
        std::map<std::string, std::string>::iterator iter_cgi = session_para.find("URL");
        if (iter_host != session_para.end() && iter_cgi != session_para.end())
        {
            sprintf(str_buff, "https://%s%s", iter_host->second.c_str(), iter_cgi->second.c_str());
            cpptools::json::add_string(resp, "URL", str_buff);
        }
    }

    // User-Agent
    {
        std::map<std::string, std::string>::iterator iter_agent = session_para.find("User-Agent");
        if (iter_agent != session_para.end()) {
            cpptools::json::add_string(resp, "User-Agent", iter_agent->second.c_str());
        }
    }

    // server infomations
    {
        rapidjson::Value &server_info = cpptools::json::add_object(resp, "server info");
        cpptools::json::add_number(server_info, "server ID", port, resp);
        cpptools::json::add_bool(server_info, "true", TRUE, resp);
        cpptools::json::add_bool(server_info, "false", FALSE, resp);

        rapidjson::Value &misc_info = cpptools::json::add_array(server_info, "array info", resp);
        cpptools::json::append_string(misc_info, "Hello", resp);
        cpptools::json::append_string(misc_info, "array", resp);
        cpptools::json::append_number(misc_info, 1234, resp);
        cpptools::json::append_bool(misc_info, false, resp);

        rapidjson::Value &obj_info = cpptools::json::add_object(server_info, "obj info");
        cpptools::json::add_object(obj_info, "obj info");
        cpptools::json::add_string(obj_info, "str", "a string inside");
    }

    // return
    return;
}

#endif

