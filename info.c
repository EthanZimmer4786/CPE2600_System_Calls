/**************************************************
* Filename: info.c
* Author: Ethan Zimmer
* Created: 10/29/2026
**************************************************/


#include <stdio.h>
#include <time.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>
#include <unistd.h>


static int current_time_nano(long* ns)
{
    struct timespec t;
    if (clock_gettime(CLOCK_REALTIME, &t) == 0)
    {
        *ns = t.tv_nsec;
        return 0;
    }
    return -1;
}


static int get_mem_size(long int* s)
{
    const long int size = sysconf(_SC_PAGESIZE);
    const long int total = sysconf(_SC_PHYS_PAGES);
    if (size >= 0 && total >= 0)
    {
        *s = size * total;
        return 0;
    }
    return -1;
}


int main(int argc, char* argv[])
{
    long current_time;
    if (current_time_nano(&current_time) == 0)
    {
        printf("current time (ns): %ld\n", current_time);
    }

    struct utsname uts;
    if (uname(&uts) == 0)
    {
        printf("network name: %s\n", uts.nodename);
        printf("system: %s\n", uts.sysname);
        printf("release: %s\n", uts.release);
        printf("version: %s\n", uts.version);
        printf("hardware: %s\n", uts.machine);
    }

    printf("cpus: %d\n", get_nprocs());

    long int mem_size;
    if (get_mem_size(&mem_size) == 0)
    {
        printf("memory size (bytes): %ld\n", mem_size);
    }

    return 0;
}
