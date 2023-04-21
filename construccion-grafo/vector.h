#ifndef VECTOR_H
#define VECTOR_H

typedef unsigned int u32;
typedef struct vector_head *vector;

// Returns a pointer to an initialized vector
vector vector_init(u32 size);

// Pushback an element (value) to the vector v
void vector_pushback(vector v, u32 value);

// Returns the i-th element of a vector v
u32 vector_i(vector v, u32 i);

// Returns the size of the vector v
u32 vector_size(vector v);

// Destroys the vector v
void vector_destroy(vector v);

#endif