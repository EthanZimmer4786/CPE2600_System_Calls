/**************************************************
* Filename: finfo.c
* Author: Ethan Zimmer
* Created: 10/30/2026
**************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>

#define MAX_DATE_SIZE 32


int main(int argc, char* argv[])
{
    char* filename;

    // Check for arg
    if (argc == 2)
    {
        filename = argv[1];
    } else
    {
        printf("pass a single file path to the command\n");
        return -1;
    }

    // Get file info
    struct stat fileinfo;
    if (stat(filename, &fileinfo) != 0)
    {
        printf("failed to acquire file stats for %s\n", filename);
        return -1;
    }

    // Print file type
    switch (fileinfo.st_mode & S_IFMT)
    {
        case S_IFBLK: printf("file type: Block special\n");     break;
        case S_IFCHR: printf("file type: Character special\n"); break;
        case S_IFIFO: printf("file type: FIFO special\n");      break;
        case S_IFREG: printf("file type: Regular\n");           break;
        case S_IFDIR: printf("file type: Directory\n");         break;
        case S_IFLNK: printf("file type: Symbolic link\n");     break;
        case S_IFSOCK: printf("file type: Socket\n");           break;
        default: printf("file type: Unknown\n");                break;
    }

    // Print file permissions
    printf("owner permissions: ");
    if (fileinfo.st_mode & S_IRUSR)
    {
        printf(" read");
    }
    if (fileinfo.st_mode & S_IWUSR)
    {
        printf(" write");
    }
    if (fileinfo.st_mode & S_IXUSR)
    {
        printf(" exec");
    }
    printf("\n");

    // Print id of owner
    printf("owner id: %d\n", fileinfo.st_uid);

    // Print file size
    printf("file size: %ld bytes\n", fileinfo.st_size);

    // Print last modified date
    char date_buf[MAX_DATE_SIZE];
    strftime(date_buf, sizeof(date_buf), "%d-%m-%Y %H:%M:%S", localtime(&fileinfo.st_mtim.tv_sec));
    printf("last modified: %s\n", date_buf);

    return 0;
}