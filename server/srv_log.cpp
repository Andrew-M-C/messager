
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string>
#include <sys/time.h>

#include "srv_log.h"


static const char *g_log_level_desp[] = {
    "EMERG",
    "ALERT",
    "CRIT ",
    "ERROR",
    "WARN ",
    "NOTCE",
    "INFO ",
    "DEBUG",
};


// ==========
#define __LOG_FUNCTIONS
#ifdef __LOG_FUNCTIONS

ssize_t andrewmc::messager::server::log::general_log(unsigned level, const char *file, const char *func, int line, const char *format, ...)
{
    char buff[1024];
    va_list vaList;
    size_t dateLen = 0;
    const char *log_level_string = NULL;

    if (level > LOG_DEBUG) {
        log_level_string = g_log_level_desp[0];
    } else {
        log_level_string = g_log_level_desp[level];
    }

    if (NULL == file) {
        file = "N/A";
    }
    if (NULL == func) {
        func = "N/A()";
    }

    tzset();
    time_t currSec = time(0);
    struct tm currTime;
    struct tm *pTime = localtime(&currSec);
    struct timeval currDayTime;

    gettimeofday(&currDayTime, NULL);
    if (pTime)
    {
        memcpy(&currTime, pTime, sizeof(currTime));
        dateLen = sprintf(buff, "%04d-%02d-%02d, %02d:%02d:%02d.%06ld - %s - %s, %s(), %d: ", 
                            currTime.tm_year + 1900, currTime.tm_mon + 1, currTime.tm_mday,
                            currTime.tm_hour, currTime.tm_min, currTime.tm_sec, currDayTime.tv_usec,
                            log_level_string, file, func, line);
    }

    va_start(vaList, format);
    vsnprintf((char *)(buff + dateLen), sizeof(buff) - dateLen - 1, format, vaList);
    va_end(vaList);

    dateLen = strlen(buff);
    buff[dateLen + 0] = '\n';
    buff[dateLen + 1] = '\0';

    return (write(1, buff, dateLen + 1));
}


#endif  // end of __LOG_FUNCTIONS

