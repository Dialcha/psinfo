#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/procfs.h>
#include <sys/fcntl.h>
#include <pwd.h>

char *getWaitChannel(int pid);
char *getPath(int pid);
char *getUserName(int uid);
int getBytes(int pid);
int get_info(pid_t pid);

int main(int argc, char *argv[])
{
    long x;
    if (argc < 2)
    {
        //error message
    }
    x = strtol(argv[1], NULL, 10);
    printf("Good 1\n");
    get_info(x);
}
int get_info(pid_t pid)
{
    char path[40], line[100], *p, stateChar[100], Name[100];
    FILE *statusf;
    char buf[100];
    printf("This is pid %d\n", pid);
    int uid, vM;
    snprintf(path, 40, "/proc/%d/status", pid);
    statusf = fopen(path, "r");
    if (statusf == NULL)
        return -1;

    while (fgets(buf, sizeof buf, statusf) != NULL)
    {

        sscanf(buf, "State:  %s", stateChar);
        sscanf(buf, "Name:  %s", Name);
        sscanf(buf, "Uid:     %d", &uid);
        sscanf(buf, "VmPeak: %d", &vM);
    }
    char *channel = getWaitChannel(pid);
    char *full_path = getPath(pid);
    char *user = getUserName(uid);
    int b = getBytes(pid);
    printf("State: %s\n", stateChar);
    printf("Name: %s\n", Name);
    printf("Uid: %d\n", uid);
    printf("Username: %s\n", user);
    printf("Max Virtual Memory: %d\n", vM);
    printf("Full Path: %s\n", full_path);
    printf("Bytes written to storage layer: %d\n", b);
    printf("Waiting channel: %s\n", channel);
}
char *getUserName(int uid)
{
    struct passwd *pw = getpwuid(uid);
    if (pw)
    {
        return pw->pw_name;
    }
    return "";
}
int getBytes(int pid)
{
    FILE *statusf2;
    char path[40];
    char buf2[100];
    int storage_bytes;
    snprintf(path, 40, "/proc/%d/io", pid);
    statusf2 = fopen(path, "r");
    if (statusf2 == NULL)
        return -1;

    while (fgets(buf2, sizeof buf2, statusf2) != NULL)
    {
        sscanf(buf2, "write_bytes:  %d", &storage_bytes);
        return storage_bytes;
    }
}
char *getPath(int pid)
{
    FILE *statusf3;
    char path[40];
    char buf3[100];
    char *fullpath;
    snprintf(path, 40, "/proc/%d/cmdline", pid);
    statusf3 = fopen(path, "r");
    if (statusf3 == NULL)
        return "";

    while (fgets(buf3, sizeof buf3, statusf3) != NULL)
    {
        sscanf(buf3, "/ %s", fullpath);
        return fullpath;
    }
}
char *getWaitChannel(int pid)
{
    FILE *statusf4;
    char path[40];
    char buf4[100];
    char *channel;
    channel = malloc(1024);
    /* Add error handling for malloc failure here */

    snprintf(path, 40, "/proc/%d/stack", pid);
    statusf4 = fopen(path, "r");
    if (statusf4 == NULL)
        return "";

    while (fgets(buf4, sizeof buf4, statusf4) != NULL)
    {
        sscanf(buf4, "[<c0227f4e>] %s", channel);
        return channel;
    }
}