#include <stdio.h>
#include "APIParte2.h"

int main(void) {
    Grafo g = ConstruirGrafo();
    u32* Color1 = calloc(NumeroDeVertices(g), sizeof(u32));
    u32* Color2 = calloc(NumeroDeVertices(g), sizeof(u32));
    u32* __restrict__ Orden = calloc(NumeroDeVertices(g), sizeof(u32));
    u32 min_coloreo,greedy_out;
    u32* swap;   
    /* Asigno orden natural*/
    for (u32 i=0; i<NumeroDeVertices(g); ++i) {
        Orden[i]=i;
    }
    
    min_coloreo = Greedy(g,Orden,Color1);

    for (u32 i = 0; i < 500; i++){
        if (i % 16 == 0){
            swap = Color1;
            Color1 = Color2;
            Color2 = swap;
        }

        /* [1] */
        if (OrdenImparPar(NumeroDeVertices(g),Orden,Color1) == ERROR){
            printf("Error en OrdenImparPar \n");
            return 1;
        }
        greedy_out = Greedy(g,Orden,Color1);
        min_coloreo = (min_coloreo <= greedy_out) ? min_coloreo : greedy_out; 

        /* [2] */
        if (OrdenJedi(g,Orden,Color2) == ERROR){
            printf("Error en OrdenImparPar \n");
            return 1;
        }
        greedy_out = Greedy(g,Orden,Color2);
        min_coloreo = (min_coloreo <= greedy_out) ? min_coloreo : greedy_out;
    }
    printf("Greedy coloreo con %u colores\n",min_coloreo);
    
    /* Libero memoria */
    DestruirGrafo(g);
    free(Color1);
    free(Color2);
    free(Orden);
    Color1 = NULL;
    Color2 = NULL;
    Orden = NULL;

    return 0;
}