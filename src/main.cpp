#include "main.hpp"

using namespace std;

/* Variables globales relacionadas al algoritmo*/

int P = -1;
int C, Q;
list<Cuadrado> lista_c;		//lista de cuadrados
list<Predator> lista_pd;	//lista de predadores
list<Area> lista_areas;

/* Mutex y barreras */

int *ids_threads;
pthread_mutex_t crit_section;
pthread_barrier_t sync_barriers[4];

int predador_altura;		// altura del predador que se analiza

string filename;

int main(int argc, char* argv[])
{
	string optstring = "n:";
	int opt;

	if (argc < 4)
	{
		cerr<< "Faltan argumentos"<< endl;
		exit(EXIT_FAILURE);
	}

	while ((opt = getopt(argc, argv, optstring.data() )) != -1)
		switch (opt)
		{
			case 'n':
				sscanf(optarg, "%d", &P);
				break;
			case '?':
				cerr<< "Opcion «"<< (char)optopt<< "» no reconocida."<< endl;
				exit(ERR_BAD_ARG);
		}

	if (P < 0)
	{
		cerr<< "Numero de procesos invalido"<< endl;
		exit(ERR_BAD_ARG);
	}

	filename = argv[optind];

	pthread_t* threads = Init(P, SSteps);

	for (int i=0; i< P; i++)
		pthread_join(threads[i], NULL);

	exit(EXIT_SUCCESS);
}

pthread_t* Init(int nthreads, void *(*rutina)(void*))
{
	int i = 0;
	pthread_t *threads;

	threads = (pthread_t *) malloc(nthreads * sizeof(pthread_t));
	ids_threads = (int *) malloc(nthreads * sizeof(int));

	while (i < nthreads)
	{	
		ids_threads[i] = i;
		i++;
	}

	for (i=0; i< 4; i++)
		pthread_barrier_init(&sync_barriers[i], NULL, nthreads);

	crit_section = PTHREAD_MUTEX_INITIALIZER;

	for (i=0; i< nthreads; i++)
		pthread_create(&threads[i], NULL, rutina, &ids_threads[i]);

	return threads;
}

void* SSteps(void* id_thread)
{
	const int my_pid = *(int*)id_thread; 

	int caso = 1; 

	/************************************
	 * SS0
	 ************************************/

	if (my_pid == 0)
	{
		ifstream in(filename.c_str());	//archivo de entrada.

		if (!in.is_open())
		{
			cerr<< "Imposible abrir el archivo «"<< filename<< "». Aborten."<< endl;
			exit(ERR_NO_SUCH_FILE);
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

	/* BARRERA */
	pthread_barrier_wait(&sync_barriers[0]);

	/************************************
	 * SS1
	 ************************************/

	int sub_caso =1;

	//Crear matriz dinamica de Celdas.
	Celda** matrix = NULL;
	int nfilas;

	if(my_pid == P-1)//último proceso
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

	//for(auto& predador: lista_pd)
	for (list<Predator>::iterator it_predador = lista_pd.begin(); it_predador != lista_pd.end(); ++it_predador)
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
		//for(auto& itCua:lista_c)
		for (list<Cuadrado>::iterator itCua = lista_c.begin(); itCua != lista_c.end(); ++itCua)
		{
			for(int i=0; i< nfilas; i++)
			{
				for(int j=0; j< M; j++)
				{
					if( (*itCua).pertenece(matrix[i][j].getX(), matrix[i][j].getY()) &&
							((*itCua).pertenece((*it_predador).getX(), (*it_predador).getY())))
					{//si la celda pertenece al cuadrado y ademas el cuadrado contiene al depredador
						matrix[i][j].aumentar();
					}
				}
			}
		}


		//para cada cuadrado recorrer la matrix (Cuadrados que NO contienen al predator)
		//for(auto& itCua:lista_c)
		for (list<Cuadrado>::iterator itCua = lista_c.begin(); itCua != lista_c.end(); ++itCua)
		{
			for(int i=0; i< nfilas; i++)
			{
				for(int j=0; j< M; j++)
				{
					if( (*itCua).pertenece(matrix[i][j].getX(), matrix[i][j].getY()) &&
							!((*itCua).pertenece((*it_predador).getX(), (*it_predador).getY())) )
					{//si la celda pertenece al cuadrado y ademas el cuadrado NO contiene al depredador
						matrix[i][j].setAltura(-1);
					}
				}
			}
		}

		// Ver si el proceso tiene al depredador en su matrix.
		if((*it_predador).getX()>=matrix[0][0].getX() &&
				(*it_predador).getX()< (matrix[0][0].getX()+nfilas))
		{//el proceso tiene al depredador
			///BROADCAST(altura del predador)
			(*it_predador).setAltura(matrix[(*it_predador).getX()-ajuste][(*it_predador).getY()].getAltura());

			predador_altura = (*it_predador).getAltura();
		} 

		/* BARRERA */
		pthread_barrier_wait(&sync_barriers[1]);

		/************************************
		 * SS2
		 ************************************/

		if ((*it_predador).getAltura() == -1)// no tiene la altura del predador
		{

			(*it_predador).setAltura(predador_altura);
		}

		//generar lista de áreas
		for(int i=0; i< nfilas; i++)
		{
			for(int j=0; j< M; j++)
			{
				if( (!matrix[i][j].fueVisitada()) && matrix[i][j].getAltura()==(*it_predador).getAltura())
				{//si la celda no ha sido visitada y está a la altura del predator
					Area A;
					int aux = A.recorrerArea(i, j, matrix, nfilas, M, (*it_predador));
					A.setArea(aux);

					pthread_mutex_lock(&crit_section);

					lista_areas.push_back(A);

					pthread_mutex_unlock(&crit_section);
				}
			}
		}


		/* BARRERA */
		pthread_barrier_wait(&sync_barriers[2]);

		/************************************
		 * SS3
		 ************************************/

		if(my_pid==0)
		{

			//Matching the areas
			Graph g = Graph(lista_areas.size());
			int i=0;
			int j=0;
			int index_area_con_predator=-1;
			//for(auto& A:lista_areas)
			for (list<Area>::iterator A = lista_areas.begin(); A!=lista_areas.end(); ++A)
			{
				j=0;
				if((*A).contiene_predator)
				{
					index_area_con_predator = i;
				}
				//for(auto& B:lista_areas)
				for (list<Area>::iterator B = lista_areas.begin(); B!=lista_areas.end(); ++B)
				{
					if((*A).es_adyacente((*B)))
					{
						g.addEdge(i, j);
					}
					j++;
				}
				i++;
			}
			//identificar que areas son adyacentes transitivamente con el area 
			//que contiene al predator.
			bool* ar = new bool[lista_areas.size()]; //arreglo del tamaño de la lista de areas
			for(unsigned int a=0; a< lista_areas.size(); a++){
				ar[a]=false;
			}
			g.flood(index_area_con_predator, ar);	//ar dice a que areas puede llegar el predator

			//Sumar las areas
			int areaTotal=0;
			i=0;

			for (list<Area>::iterator A = lista_areas.begin(); A!=lista_areas.end(); ++A)
			{
				if(ar[i])
				{//si el predator puede llegar a esta area
					areaTotal += (*A).getArea();
				}
				i++;
			}
			cout<< areaTotal<< endl;
		}

		/* BARRERA */
		pthread_barrier_wait(&sync_barriers[3]);
		sub_caso++;
	}//for_predator

	pthread_exit(NULL);
} 
