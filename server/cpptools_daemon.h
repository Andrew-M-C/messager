
#ifndef __CPPTOOLS_DAEMON_H__
#define __CPPTOOLS_DAEMON_H__

#include "cpp_tools.h"
#include <sys/types.h>

namespace andrewmc {
namespace cpptools {
namespace daemonize {

#define kPidUnknown     ((pid_t)0)

typedef struct stDaemonConfig {
    std::string     pid_file_path;
    std::string     work_dir_path;
    bool            should_change_path;
    bool            should_kill_stdout;
    stDaemonConfig(): work_dir_path("/"), should_change_path(false), should_kill_stdout(false) {}
} Config;


typedef struct stDaemonInfo {
    pid_t   self_pid;
    pid_t   exist_pid;
    stDaemonInfo(): self_pid(kPidUnknown), exist_pid(kPidUnknown) {}
} Info;


int daemonize(const Config &config, Info &info_out);
const char *home_dir();


}   // end of namepsace daemonize
}   // end of namepsace cpptools
}   // end of namepsace andrewmc


#endif  // eof
