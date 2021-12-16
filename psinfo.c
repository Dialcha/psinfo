#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/procfs.h>
#include <sys/fcntl.h>
#include <pwd.h>
#include<string.h>

int get_info(pid_t pid);

int main(int argc, char *argv[])
{
    long x;
    if (argc < 2)
    {
        //error message
    }
    int value=strcmp(argv[1],"-l");  
    if(value==0){
        printf("punto 2\n");
        int i, aux;
        pid_t* p;
        printf("%d\n", (argc)); 
        p = malloc(argc*sizeof(pid_t));
        for (aux = 0 ; aux < argc-2; aux++)
        {
            *(p + aux) = strtol(argv[aux+2], NULL, 10);
        }

        for (i = 0; i < argc-2; i++)
        {
            printf("%d\n", *(p+i));
        }
    }
    else{
        printf("punto1\n");
        x = strtol(argv[1], NULL, 10);
        get_info(x);
    }
}

int get_info(pid_t pid)
{
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
    printf("Nombre del proceso: %s\n", Name);
    printf("Estado: %s\n", stateChar);
    printf("Tamaño total de la imagen de memoria: %s\n", VmSize);
    printf("\tTamaño de la memoria en la región TEXT: %s\n", VmExe);
    printf("\tTamaño de la memoria en la región DATA: %s\n", VmData);
    printf("\tTamaño de la memoria en la región STACK: %s\n", VmStk);
    printf("Número de cambios de contexto realizados (voluntarios - no voluntarios): %d - %d\n", voluntary, nonvoluntary);
    fclose(statusf);
}