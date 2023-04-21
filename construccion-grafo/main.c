#include <stdio.h>
#include "APIG23.h"

int main() {
    Grafo g = ConstruirGrafo();
    
    printf("delta %u\n",Delta(g));
    printf("numero de lados %u\n",NumeroDeLados(g));
    printf("numero de vertices %u\n",NumeroDeVertices(g));

    /*
    for (u32 i = 0; i < g->V; i++){
        printf("Lado %u, grado %u \n",Nombre(i,g),Grado(i,g));
    }
    */
    
    DestruirGrafo(g);
    return 0;
}