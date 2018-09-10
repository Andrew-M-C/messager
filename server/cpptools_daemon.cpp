
#include "cpptools_daemon.h"

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <pwd.h>

using namespace andrewmc::cpptools::daemonize;

#define _DEBUG(fmt, args...)    printf("## " __FILE__ ", %d: " fmt "\n", __LINE__, ##args)

#ifndef NULL
#define NULL    ((void *)0)
#endif


static int _write_pid_to_file(const char *file_path, pid_t pid)
{
    FILE *pid_file = fopen(file_path, "w+");
    if (NULL == pid_file) {
        _DEBUG("Create PID file error: %s", strerror(errno));
        return -1;
    }

    char pid_str[16] = "";
    sprintf(pid_str, "%u", (unsigned)pid);
    _DEBUG("write pid %s to file %s", pid_str, file_path);

    fwrite(pid_str, sizeof(char), strlen(pid_str), pid_file);
    fclose(pid_file);
    pid_file = NULL;

    return 0;
}


int andrewmc::cpptools::daemonize::daemonize(const Config &config, Info &info_out)
{
    bool change_pwd_to_root = false;
    int ret = 0;

    info_out.self_pid = kPidUnknown;
    info_out.exist_pid = kPidUnknown;

    // daemon()
    if (0 == config.work_dir_path.length() || config.work_dir_path == "/")
    {
        if (config.should_change_path) {
            change_pwd_to_root = true;
        }
    }

    ret = daemon(change_pwd_to_root ? 0 : 1, config.should_kill_stdout ? 0 : 1);
    if (ret < 0) {
        _DEBUG("daemon failed: %s", strerror(errno));
        return ret;
    }

    // read self pid
    info_out.self_pid = getpid();

    // read exists pid
    // first of all, we should check if pid file exists
    if (config.pid_file_path.length() == 0) {
        _DEBUG("No pid file specified");
        return 0;
    }
    else {
        _DEBUG("PID file: %s", config.pid_file_path.c_str());
        FILE *pid_file = fopen(config.pid_file_path.c_str(), "r");
        if (NULL == pid_file)
        {
            if (ENOENT == errno)
            {
                // OK, create a new pid file
                info_out.exist_pid = info_out.self_pid;
                _write_pid_to_file(config.pid_file_path.c_str(), info_out.self_pid);
            }
            else
            {
                _DEBUG("open pid file error: %s", strerror(errno));
                return -1;
            }
        }
        else
        {
            // raed file then get pid
            char pid_str[16] = "";
            ssize_t read_len = fread(pid_str, sizeof(char), sizeof(pid_str) - 1, pid_file);
            if (read_len < 0)
            {
                fclose(pid_file);
                pid_file = NULL;
                _DEBUG("read pid file error: %s", strerror(errno));
                return read_len;
            }
            else
            {
                fclose(pid_file);
                pid_file = NULL;

                pid_str[read_len] = '\0';
                _DEBUG("got pid string: %s", pid_str);
                long pid = strtol(pid_str, NULL, 10);

                // check if pid exists
                ret = kill((pid_t)pid, 0);
                if (ret < 0)
                {
                    if (ESRCH == errno) {
                        // process does not exists
                        info_out.exist_pid = info_out.self_pid;
                        _write_pid_to_file(config.pid_file_path.c_str(), info_out.self_pid);
                    }
                    else {
                        _DEBUG("send signal to pid %u error: %s", (unsigned)pid, strerror(errno));
                        return ret;
                    }
                }
                else
                {
                    // process exists
                    _DEBUG("pid %u exists", (unsigned)pid);
                    info_out.exist_pid = (pid_t)pid;
                }
            }
        }
    }

    // change work path
    if (config.should_change_path && config.work_dir_path.length() > 0)
    {
        ret = chdir(config.work_dir_path.c_str());
        if (ret < 0) {
            _DEBUG("change dir to '%s' failed: %s", config.work_dir_path.c_str(), strerror(errno));
            return -1;
        }
    }

    // return
    _DEBUG("Success");
    return 0;
}


const char *andrewmc::cpptools::daemonize::home_dir()
{
    static char dir[5000] = "";
    if ('\0' == dir[0])
    {
        char *home = getpwuid(getuid())->pw_dir;
        _DEBUG("Got HOME: %s", home);
        strcpy(dir, home);
    }

    return dir;
}

