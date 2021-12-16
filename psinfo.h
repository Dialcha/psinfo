#ifndef __PSINFO_H_
#define __PSINFO_H_

typedef struct {
    char stateChar[100];
    char Name[100];
    char VmSize[100];
    char VmExe[100];
    char VmData[100];
    char VmStk[100];
    int *voluntary;
    int *nonvoluntary;
} Psinfo;

#endif