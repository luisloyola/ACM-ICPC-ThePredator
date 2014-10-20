#include "Predator.hpp"

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
}
