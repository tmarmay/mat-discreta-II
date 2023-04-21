#include <stdlib.h>
#include <stdio.h>
#include "vector.h"

typedef struct vector_head {
    u32* values;
    u32 size;
    u32 capacity;
} vector_head;

vector vector_init(u32 size) {
    vector v = malloc(sizeof(vector_head));
    if (v == NULL)
        printf("Error pidiendo memoria \n");
    v->size = 0;
    v->capacity = size;
    v->values = calloc(size, sizeof(u32));
    if (v->values == NULL)
        printf("Error pidiendo memoria \n");
    return v;
}

void vector_pushback(vector v, u32 value) {
    if(v->size >= v->capacity) {
        if(v->capacity > 3000)
            v->capacity = v->capacity + (v->capacity>>2);
        else
            v->capacity *= 3;
        v->values = realloc(v->values,sizeof(u32)*(v->capacity));
        if (v->values == NULL)
            printf("Error pidiendo memoria \n");
    }
    v->values[v->size] = value;
    v->size++;
}

u32 vector_i(vector v, u32 i) {
    return v->values[i];
}

u32 vector_size(vector v) {
    return v->size;
}

void vector_destroy(vector v) {
    free(v->values);
    v->values=NULL;
    free(v);
    v=NULL;
}