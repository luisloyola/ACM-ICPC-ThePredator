#include "Cuadrado.hpp"

bool Cuadrado::pertenece(int x, int y)
{
	if (x >= this.posx && y >= this.posy 
		&& x <= (this.posx + largo) && y <= (this.posy + largo))
		return true;

	return false;
}

Cuadrado::Cuadrado(int x, int y, int largo) throw error_cuadrado
{
	if (x < 0 || y < 0 || largo < 0)
		throw error_cuadrado.MAL_PARAMETRO;

	this->x = x;
	this->y = y;
	this->largo = largo;
}
