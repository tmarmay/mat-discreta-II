#ifndef ESTRUC_GRAF_H
#define ESTRUC_GRAF_H

#include <stdbool.h>
#include "vector.h"

typedef unsigned int u32;

typedef struct GrafoSt {
    vector* vertex;
    u32* __restrict__ name;
    u32 V;
    u32 E;
    u32 degree;
    bool* __restrict__ init;
} GrafoSt;

#endif