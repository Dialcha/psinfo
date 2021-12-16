#include <stddef.h>
#include <stdlib.h>
#include "dynamicArray.h"

void initArray(Array *a, size_t initialSize){

    a->process=malloc(initialSize * sizeof(int));
    a->used=0;
    a->size=initialSize;
}

void inserArray(Array *a, Psinfo element) {
    if(a->used == a->size) {
        a->size *= 2;
        a->process=realloc(a->process, a->size * sizeof(int));
    }
    a->process[a->used++]=element;
}

void freeArray(Array *a) {
    free(a->process);
    a->process = NULL;
    a -> used = a->size = 0;
}