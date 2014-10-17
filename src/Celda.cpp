#include "Celda.hpp"

Celda::Celda()
{
	visitada = false;
	contiene_predador = false;
	altura = 0;

	posX = posY = 0;
}

Celda::Celda(int x, int y)
{
	visitada = false;
	contiene_predador = false;
	altura = 0;

	posX = x;
	posY = y;
}

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

bool Celda::fueVisitada()
{
	return this->visitada;
}

