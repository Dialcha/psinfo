#include <stdio.h>
#include <stdlib.h>
#include "dynamicArray.h"

int main(int argc, char *argv[]){
    Array a; 
    int i; 
    initArray(&a, 5);

    for (i = 0; i<100; i++)
        insertArray(&a, i); 

    printf("%d\n", a.process[9]);
    printf("%d\n", (int)a.used);
    freeArray(&a);
}