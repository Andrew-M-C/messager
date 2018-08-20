
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

// ==========
#define __PUBLIC_FUNCTIONS
#ifdef __PUBLIC_FUNCTIONS

void andrewmc::messager::server::cgi::test::process(andrewmc::libcoevent::TCPServer *server, std::map<std::string, std::string> &req_para, rapidjson::Document &resp)
{
    int port = server->port();
    char str_buff[1024] = "";
    tools::json_init(resp);

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
            tools::json_add_string(resp, "server time", str_buff);
        }
    }

    // client infos
    {
        std::map<std::string, std::string>::iterator iter_addr = req_para.find("X-Real-IP");
        std::map<std::string, std::string>::iterator iter_port = req_para.find("X-Real-Port");
        if (iter_addr != req_para.end() && iter_port != req_para.end())
        {
            sprintf(str_buff, "%s:%s", iter_addr->second.c_str(), iter_port->second.c_str());
            tools::json_add_string(resp, "server client", str_buff);
        }
    }

    // server infos
    {
        std::map<std::string, std::string>::iterator iter_host = req_para.find("Host");
        std::map<std::string, std::string>::iterator iter_cgi = req_para.find("URL");
        if (iter_host != req_para.end() && iter_cgi != req_para.end())
        {
            sprintf(str_buff, "https://%s%s", iter_host->second.c_str(), iter_cgi->second.c_str());
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

    // return
    return;
}

#endif

