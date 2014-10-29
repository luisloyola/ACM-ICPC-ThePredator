#include "comunicacion.hpp"
#include "Area.hpp"
#include "Cuadrado.hpp"
#include "Predator.hpp"

#include <iostream>

#include <mpi.h>

#ifndef MPI_
	#define MPI_ MPI::COMM_WORLD
#endif

#define END_TAG 363

using namespace std;

void send(list<Cuadrado> &lista, int pid)
{
	for (auto &sqr: lista)
	{
		sqr.send(pid);
	}
}

void send(list<Area> &lista, int pid)
{
	for (auto &sqr: lista)
	{
		sqr.send(pid);
	} 
	int fin = 0;

	MPI_.Send(&fin, 1, MPI::INT, pid, END_TAG);
}

void send(list<Predator> &lista, int pid)
{
	for (auto &sqr: lista)
	{
		sqr.send(pid);
	} 
}

void Bcast(list<Predator> &lista, int root)
{
	int pid = MPI_.Get_rank();
	int nproc = MPI_.Get_size();
	int buffer[2];
	MPI::Status estado; 

	if (pid == root)
	{
		for (int i=0; i< nproc; i++)
		{
			if (i != root)
			{ 
				send(lista, i);
				MPI_.Send(&pid, 1, MPI::INT, i, END_TAG);
			}
		}
	}

	else
	{
		int tag = END_TAG;
		do
		{
			MPI_.Probe(root, MPI::ANY_TAG, estado);
			tag  = estado.Get_tag();

			if (tag == Predator::TAG)
			{
				MPI_.Recv(buffer, 2, MPI::INT, root, Predator::TAG);

				Predator aux(buffer[0], buffer[1]);

				lista.push_back(aux); 
			}
			else if (tag == END_TAG)
				MPI_.Recv(buffer, 1, MPI::INT, root, END_TAG);

		}while(tag != END_TAG); 
	}
}

void Bcast(list<Cuadrado> &lista, int root)
{
	int pid = MPI_.Get_rank();
	int nproc = MPI_.Get_size();
	int buffer[3];
	MPI::Status estado; 

	if (pid == root)
	{
		for (int i=0; i< nproc; i++)
		{
			if (i != root)
			{ 
				send(lista, i);
				MPI_.Send(&pid, 1, MPI::INT, i, END_TAG);
			}
		}
	}

	else
	{
		int tag = END_TAG;
		do
		{
			MPI_.Probe(root, MPI::ANY_TAG, estado);
			tag  = estado.Get_tag();

			if (tag == Cuadrado::TAG)
			{
				MPI_.Recv(buffer, 3, MPI::INT, root, Cuadrado::TAG);

				Cuadrado aux(buffer[0], buffer[1], buffer[2]);

				lista.push_back(aux); 
			}
			else if (tag == END_TAG)
				MPI_.Recv(buffer, 1, MPI::INT, root, END_TAG);

		}while(tag != END_TAG); 
	}
}

void Gather(list<Area> &lista, int recp_pid)
{
	int cont = 0;	// contador que indica cuantas listas a recibido
	int conf;		// variable para recibir la confirmacion

	int pid = MPI_.Get_rank();
	int nproc = MPI_.Get_size();

	int* msg;		// es donde se recibe el 'Area'
	int count;

	MPI::Status estado;

	if (pid != recp_pid)
	{
		send(lista, recp_pid);
	}

	else	// pid == recp_pid
	{
		while (cont < (nproc - 1))
		{
			MPI_.Probe(MPI::ANY_SOURCE, MPI::ANY_TAG, estado);

			switch (estado.Get_tag())
			{
				case END_TAG:
					MPI_.Recv(&conf, 1, MPI::INT, MPI::ANY_SOURCE, END_TAG);
					cont++;
					break;
				
				case Area::TAG:
					count = estado.Get_count(MPI::INT);
					msg = (int*) malloc(count * sizeof(int));

					if (msg == NULL) MPI_.Abort(MPI::ERR_NO_MEM);

					MPI_.Recv(msg, count, MPI::INT, MPI::ANY_SOURCE, Area::TAG);

					Area aux(msg);
					lista.push_back(aux); 
					break;
			}
		}
	}
}

