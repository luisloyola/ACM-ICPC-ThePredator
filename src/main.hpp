#ifndef H_MAIN
#define H_MAIN

#include <fstream>
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "Cuadrado.hpp"
#include "Predator.hpp"
#include "Area.hpp"
#include "Celda.hpp"
#include "Graph.hpp"

#include <pthread.h>

enum Error {ERR_NO_SUCH_FILE=1, ERR_NO_MEM, ERR_BAD_ARG};	// Errores posibles

#define M 10000

/**
 * Funcion que deben ejecutar todas las hebras del proceso.
 *
 * @param id_thread	Id que identifica a cada hebra particularmente. Se debe 
 * empezar de 0.
 *
 * @return 
 */
void* SSteps(void* id_thread);

/**
 * Inicializa «nthreads» hilos que ejecutan la funcion «rutina», pasandoles un 
 * id unico a cada uno de los hilos.
 *  
 * @param nthreads	Numero de threads que se inicializan
 * @param rutina	Es la funcion que ejecutan todas las hebras 
 *
 * @return Un arreglo de 'pthread_t' (pthread_t *) de tamaño «nthreads»
 */
pthread_t* Init(int nthreads, void *(*rutina)(void*));

#endif
