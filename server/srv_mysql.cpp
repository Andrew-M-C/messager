
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string>
#include <sys/time.h>

#include "srv_mysql.h"

using namespace andrewmc::messager::server::mysql;

#if 1
    static const char *g_username = "root";
    static const char *g_password = "root";
    static const char *g_db_name = "messager";
    static const char *g_ipaddr = "127.0.0.1";
    static const int g_port = 3306;
#else
#endif

// ==========
#define __PUBLIC_FUNCTIONS
#ifdef __PUBLIC_FUNCTIONS

const char *andrewmc::messager::server::mysql::username()
{
    return g_username;
}


const char *andrewmc::messager::server::mysql::password()
{
    return g_password;
}


const char *andrewmc::messager::server::mysql::database_name()
{
    return g_db_name;
}


const char *andrewmc::messager::server::mysql::ipaddress()
{
    return g_ipaddr;
}


int andrewmc::messager::server::mysql::port()
{
    return g_port;
}


#endif  // end of __PUBLIC_FUNCTIONS

