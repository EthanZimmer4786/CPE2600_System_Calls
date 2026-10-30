/**************************************************
* Filename: pmod.c
* Author: Ethan Zimmer
* Created: 10/30/2026
* Run: sudo ./pmod
**************************************************/

#include <stdio.h>
#include <time.h>
#include <sys/resource.h>
#include <unistd.h>


int main(int argc, char* argv[])
{
    printf("initialized priority: %d\n", getpriority(PRIO_PROCESS, 0));

    // Modify priority
    nice(-10);

    printf("modified priority: %d\n", getpriority(PRIO_PROCESS, 0));

    // Sleep
    const struct timespec ts = {.tv_sec = 1, .tv_nsec = 837272638L};
    if (nanosleep(&ts, NULL) != 0)
    {
        printf("Sleep interrupted\n");
        return -1;
    }

    printf("goodbye!\n");

    return 0;
}