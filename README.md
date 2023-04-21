# Matematica Discreta II (Famaf 2023)

## Integrantes 
- Ignacio Cuevas
- Tomas Marmay 

## Grafos

En este proyecto se va a estar trabajando sobre procesamiento y algoritmos en grafos en el lenguaje de C. 
Basicamente se basa en dos partes. La primera parte se trata sobre procesar un grafo dado en formato DIMACS (con leve modificaciones) y construir funciones basicas.
Y en la segunda parte del trabajo se trata sobre colorear un grafo usando el algoritmo de Greedy. Dado que Greedy garantiza dar el color cromatico pero **solo** si se lo corre con todos los ordenamientos de vertices posibles, algo que no es factible por nivel de tiempo y eficiencia ya que hay **n!** ordenamientos posibles, lo que se hace es tratar de aproximarlo. Esto lo hace dando ordenes mezclados para "simular" que veo todas las ordenaciones posibles.


### Primera parte

Debido a que los nombres de los vertices pueden ser cualquier numero entero entre 0 y 2<sup>32</sup> decidimos usar una funcion de hash para "mapear" cada nodo i con un nuevo nombre j:

$$
\begin{align}
has(i) = j\\
\end{align}
$$

para despues manejarse internamente con los nuevos nombres.
La parte mas costosa en cuanto a complejidad es en poder mapear los nodos con un nuevo nombre. Dada nuestra implementacion sabemos que nuestro algoritmo es muy eficiente para los casos en los que los nodos de entrada no son multiplos de la cantidad de `vertices`. Y nuestro peor caso sucede cuendo lo anterior pasa ya que se incrementa el numero de coaliciones y es costoso resolverlas.

> Para mas detalles sobre la parte uno ver `consignas-parte1.pdf`
#### Archivos

- `APIG23.h` : Prototipo de funciones sobre el grafo
- `APIG23.c` : Implementacion de procesamiento de grafo y funciones
- `EstructuraGrafo23.h` : Estructura interna del grafo
- `rbt.h` : Prototipo de funciones de red-black-tree
  - Se encargar de resolver problema de coaliciones
- `rbt.c` : Implementacion de red-black-tree
- `vector.h` : Estructura de vector y funcions
- `vector.c` : Implementacion de vector y funciones
- `Makefile` : Para simplificar la compilacion de la parte1 del proyecto 
  
#### Tiempos de referencia

Nuestro algoritmo tienen los siguientes tiempos en peor y mejor caso, hablando sobre grafos significativamente importantes:

|Grafo                |Vertices-Aristas                          |Tiempo                         |
|----------------|-------------------------------|-----------------------------|
|Gf12345_12111222|`221651-12528006 `            |27 seg            |
|R1999999_10123123          |`2000000-7196008`            |1,6 seg            |

#### Posibles mejoras

- Si se cambiara la funcion de hash por una mas compleja, lo que significa que va a haber menos coliciones el tiempo de ejecucion del peor caso bajaria drasticamente, sin contar que no seria de falta el uso de rbt y el over-head que produce
- Todo el proyecto seria mejor diseñado y con mas rendimiento si fuera implementado en C++.

### Segunda parte

Usamos la primer parte del proyecto para procesar el grafo. 
Luego comenzamos con el proceso de coloreo:
- [0] Correr Greedy en el orden natural (una vez, para generar un coloreo inicial).
- [1] Corren OrdenImparPar y a continuacion Greedy con ese orden.
- [2] Simultaneamente corren OrdenJedi y Greedy con ese orden.

Obviamente los coloreos obtenidos en [1] y [2] deben ser guardados en distintos arrays.
Se repiten [1] y [2] 16 veces, y luego se intercambian las estrategias: el array donde se guardaba el coloreo de [1] ahora se procesa usando la estrategia [2] y viceversa.
Cada 16 veces se alternan las estrategias. En total deben correr 500 veces [1] y 500 veces [2] (es decir, que el total de Greedys sin contar los primeros seran 1000).

Esto nos va a garantizar que greedy tenga distintos ordenamientos y con suerte podremos dar justo con el ordenamiento que despues de correr Greedy da el numero cromatico del grafo leido por stdin.

> Para mas detalle de como funciona OrdenImparPar y OrdenJedi ver `consignas-parte2.pdf`

#### Archivos
- `APIParte2.h` : Especificacion de Greedy y funciones de ordenes.
- `APIParte2.c` : Implementacion de Greedy y funciones de ordenes.
- `main.c` : Colorea un grafo G ingresado por stdin y imprime aproximacion del numero cromatico o el mismo numero cromatico.
- `Makefile` : Para simplificar la compilacion de la parte2 del proyecto 
#### Posibles mejoras

- Cuanto mas complejas sean las funciones de ordenamiento mas seguro va a ser que nuestro algoritmo converga a la solucion correcta. Por lo que si llamamos mas veces a nuestras funciones de ordenamientos o añadimos nuevas va a mejorar nuestro algoritmo.
- Si bien la complejidad del coloreo depende de la implementacion de la parte 1, cuanto mas eficientes sean las funciones de ordenamiento mas va a ayudar al tiempo final, ya que se ejecutan muchas veces.
