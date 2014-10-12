#include "Cuadrado.hpp"

bool Cuadrado::pertenece(int x, int y)
{
	if (x >= this->posx && y >= this->posy
		&& x <= (this->posx + largo) && y <= (this->posy + largo))
		return true;

	return false;
}

Cuadrado::Cuadrado(int x, int y, int largo)
{
	if (x < 0 || y < 0 || largo < 0)
		throw std::invalid_argument("Parametros no validos");

	this->posx = x;
	this->posy = y;
	this->largo = largo;
}
