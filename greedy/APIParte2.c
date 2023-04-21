#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include "APIParte2.h"

inline static u32 max(u32 x, u32 y) {
    return (x>y)?x:y;
}

u32 Greedy(Grafo G,u32* Orden,u32* Color) {
    u32 V = NumeroDeVertices(G);
    u32 max_color = 1;
    bool* __restrict__ coloured = calloc(V, sizeof(bool));   // dice si el i-esimo nodo esta coloreado
    bool* __restrict__ color_set = calloc(V, sizeof(bool));    // dice si el i-esimo color esta usado

    if (coloured == NULL || color_set == NULL){
        printf("Error en greedy \n");
        return MAX_RANGE;
    }

    Color[Orden[0]] = 0;
    coloured[Orden[0]] = true;

    for (u32 i = 1; i < V; ++i) {
        u32 min_number = 0, max_vec = 0;
        {                                       // busca el minimo color para Orden[i]
            for (u32 j = 0; j < Grado(Orden[i],G); j++) {
                if (coloured[IndiceVecino(j,Orden[i],G)]) {
                    color_set[Color[IndiceVecino(j,Orden[i],G)]] = true;
                    max_vec = max(max_vec, Color[IndiceVecino(j,Orden[i],G)]);
                }
            }
            while (color_set[min_number]) {
                min_number++;
            }
            max_color = max(max_color, min_number);
        }
        Color[Orden[i]] = min_number;
        coloured[Orden[i]] = true;

        for (u32 j = 0; j <= max_vec; ++j)
            color_set[j] = false;
    }

    free(coloured);
    coloured = NULL;
    free(color_set);
    color_set = NULL;

    assert(Delta(G) >= max_color);      // propiedad de grafo

    return max_color+1;
}

char OrdenImparPar(u32 n,u32* Orden,u32* Color) {
    // funcion para comparar entre F(x)
    int compare (const void *a, const void *b) {
        u32 *x = (u32 *)a;
        u32 *y = (u32 *)b;

        if (Color[*x]%2 == Color[*y]%2)
            return (Color[*y] - Color[*x]);
        else
            if (Color[*x]%2)
                return -1;
            else
                return 1;
    }

    // ordeno los vertices con la funcion custom
    qsort(Orden, n, sizeof(u32), compare);

    return '0';
}

char OrdenJedi(Grafo G,u32* Orden,u32* Color) {
    u32* __restrict__ sums = calloc(NumeroDeVertices(G), sizeof(u32));
    
    if (sums == NULL){
        printf("Error en orden jedi \n");
        return '1';
    }
    // calculo F(x) para cada color
    for (u32 i = 1; i < NumeroDeVertices(G); ++i) {
        sums[Color[i]] += Grado(i,G);
    }
    for (u32 i = 1; i < NumeroDeVertices(G); ++i) {
        if (sums[i]) sums[i] *= i;
        else break;
    }
    // funcion para comparar entre F(x)
    int compare (const void *a, const void *b) {
        u32 *x = (u32 *)a;
        u32 *y = (u32 *)b;
        
        return (sums[Color[*y]] - sums[Color[*x]]);
    }

    // ordeno los vertices con la funcion custom
    qsort(Orden, NumeroDeVertices(G), sizeof(u32), compare);

    free(sums);
    sums = NULL;

    return '0';
}
