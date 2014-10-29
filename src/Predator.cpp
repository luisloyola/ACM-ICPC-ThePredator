#include "Predator.hpp"
#include <mpi.h>

int Predator::getX()
{
	return this->posx;
}

int Predator::getY()
{
	return this->posy;
}

int Predator::getAltura()
{
	return this->altura;
}
		 
void Predator::setAltura(int alt)
{
	this->altura = alt;
} 

Predator::Predator(int x, int y)
{
	if (x < 0 || y < 0)
		throw std::invalid_argument("Parametros no validos");

	this->posx = x;
	this->posy = y;
	altura = -1;
}

void Predator::send(int pid)
{
	int data[2];

	data[0] = posx;
	data[1] = posy;

	MPI::COMM_WORLD.Send(data, 2, MPI::INT, pid, Predator::TAG);
}
