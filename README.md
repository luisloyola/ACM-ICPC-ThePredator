# Problema

El problema original se presenta en la pagina *UVa Online Judge*: [aquí](http://uva.onlinejudge.org/index.php?option=onlinejudge&Itemid=8&page=show_problem&problem=1805)

Se tiene una matriz de 10000 x 10000, una lista de cuadrados (puestos dentro de 
la matriz) y la coordenada de un depredador **X**. Estos cuadrados pueden 
superponerse (solaparse) dentro de la matriz generando nuevos "compartimentos". 
La idea es que, dada la coordenada de **X** (depredador), calcular el área que 
puede recorrer esta **X**. Es decir, entregar el área (en celdas) que tiene el 
compartimento en el que se encuentra **X**.

![Captura de pantalla de 2014-10-23 22:56:56.png](https://bitbucket.org/repo/EpgGeK/images/1384335021-Captura%20de%20pantalla%20de%202014-10-23%2022:56:56.png)

En la figura anterior se presenta una fracción de la matriz.

## Entrada

La entrada consiste en múltiples casos de prueba. Cada caso empieza con un 
entero **C**, que determina el numero de cuadrados puestos en la matriz. Las 
siguientes **C** lineas se componen de 3 enteros cada una, representando la 
ubicación de cada cuadrado dentro de la matriz con el formato (f, c, l): **f** 
es el numero de fila, **c** es el numero de columna y **l** es el largo del 
cuadrado.

La siguiente linea es un entero **Q** que dice cuantos predadores hay en el 
caso anterior. Las siguientes **Q** lineas constan de 2 enteros cada una, 
representando las coordenadas de cada depredador dentro de la matriz.

Ejm.

El siguiente ejemplo de entrada es con 1 solo caso.

	3
	2 2 5
	3 5 3
	4 4 5
	3
	6 4
	3 7
	10000 10000

## Salida

Ejm

Siguiendo el mismo ejemplo anterior; la salida sería:

	Caso 1:
	5
	1
	99999958

# Compilación

Para compilar el programa, diríjase a la carpeta del laboratorio (lab1/) y 
ejecute el comando `make`. Esto generará el código objeto de los archivos 
fuente y también el ejecutable «lab1»

**Requisitos:**

 - GCC (GNU compiler collection)
 - El estandar c++11
 - Alguna implementacion de MPI: mpich, mpich2, openMPI, etc.

# Ejecución

En la carpeta en donde se creo el ejecutable escriba en la terminal:

	mpirun -n NUM_PROC ./lab1 FILE

Donde **NUM_PROC** es el numero de procesos en paralelo que quiere que sean 
ejecutados, y **FILE** es el archivo de entrada.
