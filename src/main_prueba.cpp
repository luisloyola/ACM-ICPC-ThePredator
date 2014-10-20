#include <iostream>
#include <fstream>
#include <list>


#include "Area.hpp"
#include "Celda.hpp"
#include "comunicacion.hpp"
#include "Cuadrado.hpp"
#include "Graph.hpp"
#include "Predator.hpp"

extern "C"
{
#include <bsp.h>
}

void print(Cuadrado &sqr);

using namespace std;

string filename;

void bsp_main();
int main(int argc, char* argv[])
{
	bsp_init(bsp_main, argc, argv);

	if (argc < 2)
		cerr<< "Faltan argumentos"<< endl;

	else
	{
		filename = argv[1];
		bsp_main();
	}
}

void bsp_main()
{
	bsp_begin(bsp_nprocs());

	int P = bsp_nprocs();
	int pid = bsp_pid();

	int C, Q;
	list<Cuadrado> lista_c;
	list<Predator> lista_pd;

	/****************************************
	 * SS0
	 ****************************************/

	if (pid == 0)
	{
		ifstream entrada(filename.data());
		int data[3];

		entrada >> C;

		for (int i=0; i< C; i++)
		{
			entrada >> data[0] >> data[1] >> data[2]; 
			
			Cuadrado aux(data[0], data[1], data[2]);

			lista_c.push_back(aux);
		}

		entrada >> Q;

		for (int i=0; i< Q; i++)
		{
			entrada >> data[0] >> data[1];

			Predator aux(data[0], data[1]);

			lista_pd.push_back(aux);
		}
	}


	bsp_end();
}

void print(Cuadrado &sqr)
{
	cout<< "Coordenada x:\t"<< sqr.getX()<< endl;
	cout<< "Coordenada y:\t"<< sqr.getY()<< endl;
	cout<< "Largo:\t\t"<< sqr.getLargo()<< endl;
}
