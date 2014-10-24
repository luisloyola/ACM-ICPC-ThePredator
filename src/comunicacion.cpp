#include "comunicacion.hpp"
#include "Area.hpp"
#include "Cuadrado.hpp"
#include "Predator.hpp"

extern "C"
{
#include <bsp.h>
}

using namespace std;

void get_areas(list<Area> &destino)
{
	int cuantos, tamanio;

	bsp_qsize(&cuantos, &tamanio); 

	int* msg = (int*) malloc(tamanio);

	if (msg == NULL) 
		bsp_abort("No se pudo reservar memoria suficiente para recibir las areas");

	for (int i=0; i< cuantos; i++)
	{
		bsp_move(msg, tamanio);

		Area nueva(msg[0]);

		nueva.contiene_predator = (msg[1] == 1 ? true:false);

		int j;

		for (j=4; j< 4+2*msg[2]; j+=2)
		{
			nueva.add_celda_sup(msg[j], msg[j+1]);
		}

		for (; j< 4+2*(msg[2] + msg[3]); j+=2)
		{
			nueva.add_celda_inf(msg[j], msg[j+1]);
		}

		destino.push_back(nueva);
	}
	free(msg);
}

void get_cuadrados(list<Cuadrado> &destino)
{
	int cuantos, tamanio;
	int newsqr[3];

	bsp_qsize(&cuantos, &tamanio); 


	for (int i=0; i< cuantos; i++)
	{
		bsp_move(newsqr, 3*sizeof(int));

		Cuadrado nuevo(newsqr[0], newsqr[1], newsqr[2]); 

		destino.push_back(nuevo);
	}
}

void get_predadores(list<Predator> &destino)
{
	int cuantos, tamanio;
	int data_pred[2];

	bsp_qsize(&cuantos, &tamanio); 

	for (int i=0; i< cuantos; i++)
	{
		bsp_move(data_pred, 2*sizeof(int));

		Predator aux(data_pred[0], data_pred[1]); 

		destino.push_back(aux);
	} 
}

void send(int pid, list<Cuadrado> &lista)
{
	for (auto &sqr: lista)
	{
		sqr.send(pid);
	}
}

void send(int pid, list<Area> &lista)
{
	for (auto &sqr: lista)
	{
		sqr.send(pid);
	} 
}

void send(int pid, list<Predator> &lista)
{
	for (auto &sqr: lista)
	{
		sqr.send(pid);
	} 
}
