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
void Celda::setXY(int x, int y)
{
	this->posX = x;
	this->posY = y;
}  

int Celda::getX()
{
	return this->posX;
}

int Celda::getY()
{
	return this->posY;
}

void Celda::visitar()
{
	this->visitada = true;
}

bool Celda::esVisitada()
{
	return this->visitada;
}

/*Celda::Celda(int a)
{
	this->altura = a;
}
*/
