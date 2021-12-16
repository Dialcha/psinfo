#ifndef __ARRAYSTRUCT_H_
#define __ARRAYSTRUCT_H_
#include <stddef.h>
#include "psinfo.h"

typedef struct {
    Psinfo *process; //se cambio array por process
    size_t used;
    size_t size;
} Array;

void initArray(Array *a, size_t initialSize);
void insertArray(Array *a, int element);
void freeArray(Array *a);

#endif
