#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/procfs.h>
#include <sys/fcntl.h>
#include <pwd.h>
#include "psinfo.h"

int get_info(pid_t pid)
{
    Psinfo pidInfo;
    char path[40], line[100], *p, stateChar[100], Name[100], VmExe[100], VmData[100], VmStk[100], VmSize[100];
    FILE *statusf;
    char buf[100];
    int voluntary, nonvoluntary;
    snprintf(path, 40, "/proc/%d/status", pid);
    statusf = fopen(path, "r");
    if (statusf == NULL)
        return -1;

    while (fgets(buf, sizeof buf, statusf) != NULL)
    {
        sscanf(buf, "State:  %s", stateChar);
        sscanf(buf, "Name:  %s", Name);
        sscanf(buf, "VmSize: %s", VmSize);
        sscanf(buf, "VmExe: %s", VmExe);
        sscanf(buf, "VmData: %s", VmData);
        sscanf(buf, "VmStk: %s", VmStk);
        sscanf(buf, "voluntary_ctxt_switches: %d", &voluntary);
        sscanf(buf, "nonvoluntary_ctxt_switches: %d", &nonvoluntary);
    }

    strcpy(pidInfo.Name, Name);



}