#include <fstream>
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include "Cuadrado.hpp"
#include "Predator.hpp"
#include "Area.hpp"
#include "Celda.hpp"
#include "Graph.hpp"
#include "comunicacion.hpp"

extern "C"
{
#include <bsp.h>
}

#define M 10

using namespace std;

void bsp_main();

string filename;

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

	return 0;
}

void bsp_main()
{
	bsp_begin(bsp_nprocs());

	int P = bsp_nprocs();
	int pid = bsp_pid();

	int C, Q;
	list<Cuadrado> lista_c;
	list<Predator> lista_pd;

	/************************************
	 * SS0
	 ************************************/

	if (pid == 0)
	{
		ifstream in(filename);	//archivo de entrada.

		if (!in.is_open())
		{
			bsp_abort("No se encontro el archivo %s", filename.data());
		}

		in >> C;

		for(int i=0; i< C; i++)
		{//para cada cuadrado
			int r, c, s;
			in >> r >> c >> s;
			//cout << "r:" << r << " c:" << c << " s:" << s << endl;
			Cuadrado cua_aux = Cuadrado(r-1, c-1, s);	//crear un cuadrado en el stack
			lista_c.push_back(cua_aux);			//copia ese cuadrado en una lista
		}

		in >> Q;
		for(int i=0; i< Q; i++)
		{//para cada predator
			int pr, pc;
			in >> pr >> pc;
			//cout<< "pr:" << pr << " pc:" << pc << endl;
			Predator pre_aux =  Predator(pr-1, pc-1);	//crear un depredador en el stack	
			lista_pd.push_back(pre_aux);			//copia ese predador en una lista
		}
	}

	///P0 hace broadcast de la lista de cuadrados y la lista de predadores

	if (pid == 0)
	{
		int num_pred = lista_pd.size();

		for (int i=1; i< P; i++)
		{
			bsp_send(i, 0, &num_pred, sizeof(int));
		}
	}
	bsp_sync();

	if (pid == 0)
	{
		for (int i=1; i< P; i++)
		{
			send(i, lista_pd);
		}
	}
	bsp_sync();

	if (pid == 0)
	{
		for (int i=1; i< P; i++)
		{
			send(i, lista_c);
		}
	}
	bsp_sync();

	/************************************
	 * SS1
	 ************************************/

	if (pid != 0)
	{
		int num_pred;
		bsp_move(&num_pred, sizeof(int));

		get_predadores(lista_pd, num_pred);
		get_cuadrados(lista_c);
	}

	int sub_caso =1;

	for(auto& predador: lista_pd)
	{

		//Crear matriz dinamica de Celdas.
		Celda** matrix = NULL;
		int nfilas;
		if(pid==P-1)//último proceso
		{
			nfilas = M-(M/P*(P-1));		//el último proceso tiene todas las filas que quedan.
		}else{//cualquier otro proceso
			nfilas = M/P;				//franjas de la matriz total de M/P
		}
		matrix = new Celda*[nfilas];
		for(int i =0; i< nfilas; i++)
		{
			matrix[i] = new Celda[M];
		}

		//Inicializar matriz con celdas de altura 0 y asignar sus posiciones X e Y
		int ajuste = M/P*pid; //cada proceso tiene una franja de la matriz total.
		for(int i=0; i< nfilas; i++)
		{
			for(int j=0; j< M; j++)
			{
				matrix[i][j].setAltura(0);
				matrix[i][j].setXY(i+ajuste, j);
			}
		}


		//Recorrer matrix de celdas (Cuadrados que contienen al predator)

		//para cada cuadrado recorrer la matrix
		for(auto& itCua:lista_c)
		{
			for(int i=0; i< nfilas; i++)
			{
				for(int j=0; j< M; j++)
				{
					if( itCua.pertenece(matrix[i][j].getX(), matrix[i][j].getY()) &&
							(itCua.pertenece(predador.getX(), predador.getY())))
					{//si la celda pertenece al cuadrado y ademas el cuadrado contiene al depredador
						matrix[i][j].aumentar();
					}
				}
			}
		}


		//para cada cuadrado recorrer la matrix (Cuadrados que NO contienen al predator)
		for(auto& itCua:lista_c)
		{
			for(int i=0; i< nfilas; i++)
			{
				for(int j=0; j< M; j++)
				{
					if( itCua.pertenece(matrix[i][j].getX(), matrix[i][j].getY()) &&
							!(itCua.pertenece(predador.getX(), predador.getY())) )
					{//si la celda pertenece al cuadrado y ademas el cuadrado NO contiene al depredador
						matrix[i][j].setAltura(-1);
					}
				}
			}
		}

		predador.setAltura(matrix[predador.getX()-ajuste][predador.getY()].getAltura());


		// Ver si el proceso tiene al depredador en su matrix.
		if(predador.getX()>=matrix[0][0].getX() &&
				predador.getX()< (matrix[0][0].getX()+nfilas))
		{//el proceso tiene al depredador
			///BROADCAST(altura del predador)
			int altura = predador.getAltura();

			for(int i=0; i< P; i++)
			{
				if(i != pid)
				{
					bsp_send(i, 0, &altura, sizeof(int));
				}
			}		
		}

		bsp_sync();

		/************************************
		 * SS2
		 ************************************/

		if (predador.getAltura() == -1)// no tiene la altura del predador
		{
			int valor_predator;
			
			bsp_move(&valor_predator, sizeof(int));

			predador.setAltura(valor_predator);
		}

		//generar lista de áreas
		list<Area> LArea;
		for(int i=0; i< nfilas; i++)
		{
			for(int j=0; j< M; j++)
			{
				if( (!matrix[i][j].fueVisitada()) && matrix[i][j].getAltura()==predador.getAltura())
				{//si la celda no ha sido visitada y está a la altura del predator
					Area A;
					int aux = A.recorrerArea(i, j, matrix, nfilas, M, predador);
					A.setArea(aux);
					LArea.push_back(A);
				}
			}
		}

		//SEND LArea a PO.

		if (pid != 0)
		{
			send(0, LArea);
		}

		bsp_sync();

		/************************************
		 * SS3
		 ************************************/

		if(pid==0)
		{
			get_areas(LArea);

			//Matching the areas
			Graph g = Graph(LArea.size());
			int i=0;
			int j=0;
			int index_area_con_predator=-1;
			for(auto& A:LArea)
			{
				j=0;
				if(A.contiene_predator)
				{
					index_area_con_predator = i;
				}
				for(auto& B:LArea)
				{
					if(A.es_adyacente(B))
					{
						g.addEdge(i, j);
						cout<< i<<" es adyacente a "<< j<< endl;
					}
					j++;
				}
				i++;
			}
			//identificar que areas son adyacentes transitivamente con el area que contiene al predator.
			bool* ar = new bool[LArea.size()]; //arreglo del tamaño de la lista de areas
			for(unsigned int a=0; a< LArea.size(); a++){
				ar[a]=false;
			}
			g.flood(index_area_con_predator, ar);	//ar dice a que areas puede llegar el predator

			//Sumar las areas
			int areaTotal=0;
			i=0;
			for(auto& A:LArea){

				if(ar[i])
				{//si el predator puede llegar a esta area
					areaTotal += A.getArea();
				}
				i++;
			}
			cout<<"El area es:"<< areaTotal<< endl;
		}

		bsp_sync();
		sub_caso++;
	}//for_predator

	bsp_end();
} 
