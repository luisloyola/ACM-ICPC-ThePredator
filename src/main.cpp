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

#include <mpi.h>

#ifndef MPI_
	#define MPI_ MPI::COMM_WORLD
#endif

#define M 10000

using namespace std;

string filename;

int main(int argc, char* argv[])
{
	MPI::Init(argc, argv);
	const int P = MPI_.Get_size();
	const int my_pid = MPI_.Get_rank();

	if (my_pid == 0 && argc < 2)
	{
		cerr<< "Faltan argumentos"<< endl;
		MPI_.Abort(MPI::ERR_OTHER);
	}

	filename = argv[1];



	int caso = 1;

	int C, Q;
	list<Cuadrado> lista_c;		//lista de cuadrados
	list<Predator> lista_pd;	//lista de predadores


	/************************************
	 * SS0
	 ************************************/

	if (my_pid == 0)
	{
		ifstream in(filename);	//archivo de entrada.

		if (!in.is_open())
		{
			MPI_.Abort(MPI::ERR_NO_SUCH_FILE);
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

		in.close();
	}

	///P0 hace broadcast de la lista de cuadrados y la lista de predadores 

	Bcast(lista_pd, 0);

	Bcast(lista_c, 0);

	/************************************
	 * SS1
	 ************************************/

	int sub_caso =1;

	//Crear matriz dinamica de Celdas.
	Celda** matrix = NULL;
	int nfilas;

	if(my_pid==P-1)//último proceso
	{
		nfilas = M-(M/P*(P-1));		//el último proceso tiene todas las filas que quedan.
	}
	else
	{//cualquier otro proceso
		nfilas = M/P;				//franjas de la matriz total de M/P
	}

	matrix = new Celda*[nfilas];

	for(int i =0; i< nfilas; i++)
	{
		matrix[i] = new Celda[M];
	}

	if (my_pid == 0)
		cout<< "Caso "<< caso<< ":"<< endl;

	for(auto& predador: lista_pd)
	{


		//Inicializar matriz con celdas de altura 0 y asignar sus posiciones X e Y
		int ajuste = M/P*my_pid; //cada proceso tiene una franja de la matriz total.
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


		// Ver si el proceso tiene al depredador en su matrix.
		if(predador.getX()>=matrix[0][0].getX() &&
				predador.getX()< (matrix[0][0].getX()+nfilas))
		{//el proceso tiene al depredador
			///BROADCAST(altura del predador)
			predador.setAltura(matrix[predador.getX()-ajuste][predador.getY()].getAltura());

			int altura = predador.getAltura();

			for (int i=0; i< P; i++)
			{
				if (i != my_pid)
				{
					MPI_.Send(&altura, 1, MPI::INT, i, 0);
				}
			}
		} 

		/************************************
		 * SS2
		 ************************************/

		if (predador.getAltura() == -1)// no tiene la altura del predador
		{
			int altura;
			MPI_.Recv(&altura, 1, MPI::INT, MPI::ANY_SOURCE, 0);

			predador.setAltura(altura);
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

		Gather(LArea, 0);

		/************************************
		 * SS3
		 ************************************/

		if(my_pid==0)
		{

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
			cout<< areaTotal<< endl;
		}

		MPI_.Barrier();
		sub_caso++;
	}//for_predator

	MPI::Finalize();
} 
