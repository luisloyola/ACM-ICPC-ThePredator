#include <iostream>
#include "Area.hpp"
#include "main.hpp"
#include <mpi.h>

using namespace std;

Area::Area()
{
	area_val = 0;
	contiene_predator = false;
}

Area::Area(int valor_inicial)
{
	area_val = valor_inicial;
	contiene_predator = false;
}

Area::Area(int* buffer)
{
	area_val = buffer[0];

	contiene_predator = (buffer[1] == 1 ? true:false);

	int j;

	for (j=4; j< 4+2*buffer[2]; j+=2)
	{
		add_celda_sup(buffer[j], buffer[j+1]);
	}

	for (; j< 4+2*(buffer[2] + buffer[3]); j+=2)
	{
		add_celda_inf(buffer[j], buffer[j+1]);
	} 
}

Area::~Area()
{
	superiores.clear();
	inferiores.clear();
}

void Area::add_celda_sup(int celda_x, int celda_y)
{
	Celda nueva(celda_x, celda_y);
	superiores.push_back(nueva);
}

void Area::add_celda_inf(int celda_x, int celda_y)
{
	Celda nueva(celda_x, celda_y);
	inferiores.push_back(nueva);
}

void Area::add_celda_sup(const Celda ce)
{
	superiores.push_back(ce);
}

void Area::add_celda_inf(const Celda ce)
{
	inferiores.push_back(ce);
}

void Area::setArea(int a)
{
	this->area_val = a;
}

int Area::getArea()
{
	return this->area_val;
}

list<Celda> Area::get_sup()
{
	return this->superiores;
}

list<Celda> Area::get_inf()
{
	return this->inferiores;
}

int Area::recorrerArea(int i, int j, Celda** matrix, int nfilas, int ncolumnas, Predator pre)
{
	int area_valor = 0;
	if(!matrix[i][j].fueVisitada() && matrix[i][j].getAltura()==pre.getAltura())
	{//si la celda no ha sido visitada y está a la altura del predator.
		matrix[i][j].visitar();		//marcar celda como visitada
		area_valor++;

		if(matrix[i][j].getX()==pre.getX() && matrix[i][j].getY()==pre.getY())
		{//si la celda tiene al predador
			this->contiene_predator = true;
		}

		if(i==0)//celda de fila superior
		{
			//std::cout<<i<<","<<j<<" agregado a la lista sup"<<std::endl;
			this->superiores.push_back(matrix[i][j]);
		}
		if(i==nfilas-1)//celda de la última fila.
		{
			//std::cout<<i<<","<<j<<" agregado a la lista inf"<<std::endl;
			this->inferiores.push_back(matrix[i][j]);
		}

		//ARRIBA
		if(i!=0)
		{//NO está en la fila superior por lo que se puede preguntar por la celda superior
			area_valor += this->recorrerArea(i-1, j, matrix, nfilas, ncolumnas, pre);
		}

		//ABAJO
		if(i!=(nfilas-1))
		{//NO está en la fila inferior por lo que se puede preguntar por la celda inferior
			area_valor += this->recorrerArea(i+1, j, matrix, nfilas, ncolumnas, pre);
		}

		//IZQUIERDA
		if(j!=0)
		{//NO está en la columna izquierda por lo que se puede preguntar por la celda izquierda
			area_valor += this->recorrerArea(i, j-1, matrix, nfilas, ncolumnas, pre);
		}

		//DERECHA
		if(j!=(ncolumnas-1))
		{//NO está en la última columna por lo que se puede preguntar por la celda derecha
			area_valor += this->recorrerArea(i, j+1, matrix, nfilas, ncolumnas, pre);
		}
	}//en caso contrario hace nada y retorna 0.
	return area_valor;
}

bool Area::es_adyacente(Area& otra)
{
	for (auto& celda: inferiores)
	{
		for (auto& celda_otra:otra.get_sup())
		{
			if (celda.getX() >= celda_otra.getX())
				break;

			if (celda.getY() == celda_otra.getY() &&
				(celda_otra.getX() - celda.getX()) == 1)
			{
				return true;
			}
		}
	}

	for (auto& celda: superiores)
	{
		for (auto& celda_otra: otra.get_inf())
		{
			if (celda.getX() <= celda_otra.getX())
				break;
			if (celda.getY() == celda_otra.getY() &&
				(celda.getX() - celda_otra.getX()) == 1)
			{
				return true;
			}
		}
	}

	return false;
}

void Area::print_celdas_sup()
{
	cout<< "{";
	for (auto& celda: superiores)
	{
		cout<< "("<< celda.getX()<< ","<< celda.getY()<< "), ";
	}
	cout<< "}"<< endl;
}

void Area::print_celdas_inf()
{
	cout<< "{";
	for (auto& celda: inferiores)
	{
		cout<< "("<< celda.getX()<< ","<< celda.getY()<< "), ";
	}
	cout<< "}"<< endl;
}

void Area::send(int pid)
{ }
