#ifndef RBT_H
#define RBT_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "vector.h"
#include "APIG23.h"

typedef unsigned int u32;

typedef struct set_r {
    struct node* root;
    u32 size;
} set_r;

typedef struct set_r* set;

// Initialize set
set set_init();

// Inserts data into the set
void set_insert(set s, u32 data);

// Returns the size of the set
u32 set_size(set s);

// Specific function to organize collisions
void inorder(struct node* root, Grafo g, u32* next_free,
             vector* find_index, bool* used);

// Destroys the set
void set_destroy(set s);

#endif