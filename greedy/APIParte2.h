#ifndef APIP2_H
#define APIP2_H

#define ERROR '1'

#include "../construccion-grafo/APIG23.h" // cambiar antes de entregar

typedef unsigned int u32;

u32 Greedy(Grafo G,u32* Orden,u32* Color);

char OrdenImparPar(u32 n,u32* Orden,u32* Color);

char OrdenJedi(Grafo G,u32* Orden,u32* Color);

#endif