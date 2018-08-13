
#include <string>
#include <stdio.h>
#include <syslog.h>


#ifndef LOG_EMERG
#define LOG_EMERG   0   /* system is unusable */
#define LOG_ALERT   1   /* action must be taken immediately */
#define LOG_CRIT    2   /* critical conditions */
#define LOG_ERR     3   /* error conditions */
#define LOG_WARNING 4   /* warning conditions */
#define LOG_NOTICE  5   /* normal but significant condition */
#define LOG_INFO    6   /* informational */
#define LOG_DEBUG   7   /* debug-level messages */
#endif

#define LOG_ERROR   LOG_ERR


#ifndef NULL
#define NULL    ((void *)0)
#endif

namespace andrewmc {
namespace messager {
namespace server {
namespace log {


ssize_t general_log(unsigned level, const char *file, const char *func, int line, const char *format, ...);

#define DEBUG(fmt, args...)     general_log(LOG_DEBUG, __FILE__, __func__, __LINE__, fmt, ##args)
#define INFO(fmt, args...)      general_log(LOG_INFO, __FILE__, __func__, __LINE__, fmt, ##args)
#define NOTICE(fmt, args...)    general_log(LOG_NOTICE, __FILE__, __func__, __LINE__, fmt, ##args)
#define WARNING(fmt, args...)   general_log(LOG_WARNING, __FILE__, __func__, __LINE__, fmt, ##args)
#define ERROR(fmt, args...)     general_log(LOG_ERR, __FILE__, __func__, __LINE__, fmt, ##args)
#define CRITICAL(fmt, args...)  general_log(LOG_CRIT, __FILE__, __func__, __LINE__, fmt, ##args)
#define ALERT(fmt, args...)     general_log(LOG_ALERT, __FILE__, __func__, __LINE__, fmt, ##args)
#define EMERGENCY(fmt, args...) general_log(LOG_EMERG, __FILE__, __func__, __LINE__, fmt, ##args)

}}}}
