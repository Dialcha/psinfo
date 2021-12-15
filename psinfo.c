#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>


void main(int argc, char **argv) {
    int pid;
    char filename[1000], line[100], *p;
    FILE *f;

    sscanf(argv[1], "%d", &pid);
    printf("pid = %d\n", pid);
    sprintf(filename, "/proc/%d/stat", pid);
    f = fopen(filename, "r");
    if(!f)
        return;

    while(fgets(line, 100, f)) {
        if(strncmp(line, "State:", 6) != 0)
            continue;
        p = line + 7;
        while(isspace(*p)) ++p;

        printf("%6d %s", pid, p);
        break;
    }
}
