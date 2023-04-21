#include <stdlib.h>
#include "APIG23.h"
#include "vector.h"
#include "rbt.h"

inline static u32 hash_func(u32 a, u32 size){
    return a%size;
}

inline static u32 max(u32 a, u32 b) {
    return (a > b) ? a : b;   
}

/* Constructores */
Grafo ConstruirGrafo() {
    Grafo g = (Grafo)malloc(sizeof(GrafoSt));
    char c;
    if (g == NULL) {
        printf("Error pidiendo memoria \n");
        return NULL;
    }
    while ((c = getchar()) != EOF) {
        if (c == 'c') {
            while (c != '\n')
                c = getchar();
        }
        else if (c == 'p') {
            char word[5];
            if (!scanf("%4s %u %u\n",word,&g->V,&g->E)) {
                printf("Error leyendo los valores");
                return NULL;
            }
            g->vertex = (vector*)calloc(g->V, sizeof(vector));
            g->name = (u32*)calloc(g->V, sizeof(u32));
            g->init = (bool*)calloc(g->V, sizeof(bool));
            if (g->vertex == NULL || g->name == NULL || g->init == NULL) {
                printf("Error pidiendo memoria \n");
                return NULL;
            }
            g->degree = 0;
            break;
        }
        else 
            return NULL;
    }
    
    vector con1 = vector_init(g->E); /* Lados */
    vector con2 = vector_init(g->E);
    vector* find_index = (vector*)calloc(g->V, sizeof(vector));
    u32* next_free = (u32*)calloc(g->V, sizeof(u32));
    bool* init_fi = (bool*)calloc(g->V, sizeof(bool));
    bool* used = (bool*)calloc(g->V,sizeof(bool));

    if (find_index == NULL || next_free == NULL || init_fi == NULL || used == NULL) {
        return NULL;
    }

    /* Pedir los lados y ubicar los primeros vertices */
    set s = set_init();
    for(u32 i=0; i<g->E; i++) {
        u32 hash,x,y;
        
        if (i + 1 == g->E)
            scanf("%c %u %u",&c,&x,&y);

        else if (!scanf("%c %u %u\n",&c,&x,&y)) {
            printf("Error leyendo los valores");
            return NULL;
        }
        
        vector_pushback(con1,x);
        vector_pushback(con2,y);
        
        /* Si la posicion en hash no se uso, lo guardo alli */
        hash = hash_func(x,g->V);
        if (!used[hash]){
            g->name[hash] = x;
            next_free[hash] = hash;
            used[hash] = true;
        }
        /* Si la posicion en hash se uso, guardo x en un set */
        else if (g->name[hash] != x){
            set_insert(s,x);
            if (!init_fi[hash]){
                find_index[hash] = vector_init(1);
                init_fi[hash] = true;
            }
        }
        
        /* Lo mismo para y */
        hash = hash_func(y,g->V);
        if (!used[hash]){
            g->name[hash] = y;
            next_free[hash] = hash;
            used[hash] = true;
        }
        else if (g->name[hash] != y){
            set_insert(s,y);
            if (!init_fi[hash]){
                find_index[hash] = vector_init(1);
                init_fi[hash] = true;
            }
        }
    }

    /* Encontrar un lugar para las coliciones */
    inorder(s->root, g, next_free, find_index, used);

    /* Libero lo que ya no necesito */
    free(next_free);
    free(used);
    set_destroy(s);

    /* Armar conexiones con el nuevo mapeo */
    double coneccion_qty = ceil((0.0001*g->E)/100);
    for (u32 i=0; i < g->E; i++) {
        u32 x,y,n;

        /* Busco el indice que ocupa x en names */
        x = hash_func(vector_i(con1,i),g->V);
        if (g->name[x] != vector_i(con1,i)){
            n = vector_size(find_index[x]);
            for (u32 k = 0; k < n; k++){
                if (g->name[vector_i(find_index[x],k)] == vector_i(con1,i)){
                    x = vector_i(find_index[x],k);
                    break;
                }
            }
        }
        if (!g->init[x]){
            g->vertex[x] = vector_init((u32)coneccion_qty);
            g->init[x] = true;
        }

        /* Busco el indice que ocupa y en names */
        y = hash_func(vector_i(con2,i),g->V);
        if (g->name[y] != vector_i(con2,i)){
            n = vector_size(find_index[y]);
            for (u32 k = 0; k < n; k++){
                if (g->name[vector_i(find_index[y],k)] == vector_i(con2,i)){
                    y = vector_i(find_index[y],k);
                    break;
                }
            }
        }
        if (!g->init[y]){
            g->vertex[y] = vector_init((u32)coneccion_qty);
            g->init[y] = true;
        }

        /* Pusheo la conexion de ida y de vuelta entre x e y (orden natural) */
        vector_pushback(g->vertex[x],y);
        vector_pushback(g->vertex[y],x);
    }
    /* Destruyo los vectores donde guarde los lados */
    vector_destroy(con1);
    vector_destroy(con2);

    /* Calcular el delta del grafo */
    for (u32 i=0; i<g->V; ++i) {
        if(g->init[i])
            g->degree = max(g->degree,vector_size(g->vertex[i]));
        
        /* Aprovecho el ciclo para destruir find_index[i] */
        if (init_fi[i])
            vector_destroy(find_index[i]);
    }
    /* Libero la memoria que falta */
    free(find_index);
    free(init_fi);

    return g;
}

void DestruirGrafo(Grafo G) {
    for(u32 i=0; i<G->V; ++i) {
        if(G->init[i])
            vector_destroy(G->vertex[i]);
    }
    free(G->vertex);
    G->vertex = NULL;
    free(G->name);
    G->name = NULL;
    free(G->init);
    G->init = NULL;
    free(G);
    G = NULL;
}

/* Informacion del Grafo */
u32 NumeroDeVertices(Grafo G) {
    return G->V;
}

u32 NumeroDeLados(Grafo G) {
    return G->E;
}

u32 Delta(Grafo G){
    return G->degree;
}

/* Informacion de los Vertices */
u32 Nombre(u32 i,Grafo G){
    return G->name[i];
}

u32 Grado(u32 i,Grafo G){
    if(G->init[i])
        return vector_size(G->vertex[i]);
    return 0;
}

u32 IndiceVecino(u32 j,u32 i,Grafo G){
    if (i < G->V && j < vector_size(G->vertex[i]))
        return vector_i(G->vertex[i],j);
    else
        return MAX_RANGE;
}