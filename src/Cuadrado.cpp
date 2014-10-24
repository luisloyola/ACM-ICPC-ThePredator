#include "Cuadrado.hpp"
#include "Predator.hpp"

extern "C"
{
#include <bsp.h>
}

bool Cuadrado::pertenece(int x, int y)
{
	if (x >= this->posx && y >= this->posy
		&& x < (this->posx + largo) && y < (this->posy + largo))
		return true;

	return false;
}

bool Cuadrado::pertenece(Predator &pred)
{
	bool doesit = pertenece(pred.getX(), pred.getY());

	return doesit;
}

int Cuadrado::getX()
{
	return this->posx;
}

int Cuadrado::getY()
{
	return this->posy;
}

int Cuadrado::getLargo()
{
	return this->largo;
}

Cuadrado::Cuadrado(int x, int y, int largo)
{
	if (x < 0 || y < 0 || largo < 0)
		throw std::invalid_argument("Parametros no validos");

	this->posx = x;
	this->posy = y;
	this->largo = largo;
}

void Cuadrado::send(int pid)
{
	int data[3];

	data[0] = posx;
	data[1] = posy;
	data[2] = largo;

	bsp_send(pid, 0, data, 3*sizeof(int));
}
