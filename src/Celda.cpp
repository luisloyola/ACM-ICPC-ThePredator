#include "Celda.hpp"

void Celda::aumentar()
{
	this->altura++;
}

void Celda::setAltura(int a)
{
	this->altura = a;
}

int Celda::getAltura()
{
	return this->altura;
}

/*Celda::Celda(int a)
{
	this->altura = a;
}
*/
