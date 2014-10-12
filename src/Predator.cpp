#include "Predator.hpp"

Predator::Predator(int x, int y)
{
	if (x < 0 || y < 0)
		throw std::invalid_argument("Parametros no validos");

	this->posx = x;
	this->posy = y;
}
