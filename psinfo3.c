#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>

void getProperty(char *attrib, FILE* f);

void main(int argc, char **argv) {
    int pid;
    char filename[1000], line[100], *p;
    FILE *f;

    sscanf(argv[1], "%d", &pid);
    printf("pid = %d\n", pid);
    sprintf(filename, "/proc/%d/status", pid);
    printf("Nombre del archivo = %s\n", filename);

    f = fopen(filename, "r");
    // if(!f)
    //     fclose(f);
    //     printf("%s\n", "No entro al file");
    //     return;

    getProperty("State", f);

// FUNCIONAL
    // while(fgets(line, 100, f)) {
    //     if(strncmp(line, "State:", 6) != 0)
    //         continue;
    //     p = line + 7;
    //     while(isspace(*p)) ++p;

    //     printf("%6d %s", pid, p);
    //     break;
    // }


    fclose(f);
}

void getProperty(char *attrib, FILE *f){
    char line[100], *p;
    while(fgets(line, 100, &f)) {
        if(strncmp(line, "State:", 6) != 0)
            continue;
        p = line + 7;
        while(isspace(*p)) ++p;

        printf("%s %s", attrib, p);
        break;
    }
}
