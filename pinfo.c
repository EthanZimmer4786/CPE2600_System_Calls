/**************************************************
* Filename: pinfo.c
* Author: Ethan Zimmer
* Created: 10/29/2026
**************************************************/


#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sched.h>
#include <signal.h>


static char* get_scheduler_name(const pid_t pid)
{
    switch (sched_getscheduler(pid))
    {
    case SCHED_IDLE:
        return "idle";
    case SCHED_BATCH:
        return "batch";
    case SCHED_FIFO:
        return "fifo";
    case SCHED_RR:
        return "rr";
    case SCHED_OTHER:
        return "other";
    default:
        return "unknown";
    }
}

int main(int argc, char* argv[])
{
    int pid;
    if (argc == 1)
    {
        // Current process
        pid = getpid();
    } else if (argc == 2) {
        pid = atoi(argv[1]);

        // Check if pid exists
        if (kill(pid, 0) != 0)
        {
            printf("Cannot find pid: %d\n", pid);
            return -1;
        }
    } else
    {
        printf("Unknown command\n");
        return -1;
    }

    printf("pid: %d\n", pid);
    printf("priority: %d\n", getpriority(PRIO_PROCESS, pid));
    printf("scheduler: %s\n", get_scheduler_name(pid));

    return 0;
}