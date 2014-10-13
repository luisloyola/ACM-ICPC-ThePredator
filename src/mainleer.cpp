#include <fstream>
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include "Cuadrado.cpp"
#include "Predator.cpp"
#include "Area.cpp"
#include "Celda.cpp"

#define M 10

using namespace std;

int main(int argc, char** args)
{
	int C, Q;
	ifstream in(args[1]);
	
	if (!in.is_open())
	{
		cerr<< "No se encontro el archivo "<< args[1]<< endl;
		return 1;
	}
	
	in >> C;
	std::cout << "C:" << C << std::endl;
	std::list<Cuadrado> lista_cuadrado;
	for(int i=0;i<C;i++)
	{
		int r,c,s;
		in >> r >> c >> s;
		std::cout << "r:" << r << " c:" << c << " s:" << s <<std::endl;
		Cuadrado* cua_aux = new Cuadrado(r-1,c-1,s);	//crear un cuadrado en el heap
		lista_cuadrado.push_back(*cua_aux);			//guardar ese cuadrado en una lista
	}
	in >> Q;
	std::cout<< "Q:" << Q <<std::endl;
	std::list<Predator> lista_predator;
	for(int i=0; i<Q;i++)
	{
		int pr,pc;
		in >> pr >>pc;
		std::cout<< "pr:" << pr << " pc:" << pc << std::endl;
		Predator* pre_aux = new Predator(pr-1,pc-1);	//crear un depredador en el heap
		lista_predator.push_back(*pre_aux);			//guardar ese predador en una lista
	}
	
	
//////TESTING
	std::cout<<"TESTING:"<<std::endl;
	//Una forma de recorrer la lista con iteradores
	list<Cuadrado>::iterator itCua;
	itCua=lista_cuadrado.begin();
	for(int i=0;i<C;i++)
	{
		std::cout<< (*itCua).getX()<<"-"<<(*itCua).getY()<<"-"<<(*itCua).getLargo() <<std::endl;
		itCua++;
	}
	
	//otra forma de recorre rlista con iteradores.
	for(list<Predator>::iterator itPre = lista_predator.begin(); itPre!=lista_predator.end(); ++itPre)
	{
		std::cout<< (*itPre).getX()<<"-"<<(*itPre).getY()<<std::endl;
	}
	std::cout<<"END_TESTING"<<std::endl;
//////endTESTING
	
	//Cada maquina tiene que asignar su espacio de memoria
	int P=4;		//número de procesos a usar
	int pid=3;		//Id de cada procesador.
	Predator* pre = new Predator(5,5);
	//Celda matrix = new Celda[M/P][M];	//matrix de vertical:M/P, horizontal:M
	Celda matrix[M/P][M];
	//vector<vector<Celda>> matrix ((M/P),vector<Celda>(M));
	//matrix[3][4].altura=5;
	//std::cout<<(matrix[3][4]).altura<<std::endl;
	
	
	int nfilas;
	if(pid==P-1)
	{
		nfilas = M-(M/P*(P-1));
	}else{
		nfilas = M/P;
	}
	std::cout<<"antes de recorrer"<<std::endl;
	for(int i=0;i<nfilas;i++)
	{
		for(int j=0; j<M;j++)
		{
			matrix[i][j].setAltura(0);
			std::cout<<matrix[i][j].getAltura()<<",";
		}
		std::cout<<std::endl;
	}
	//Recorrer matrix de celdas
	int ajuste = M/P*pid;
	//para cada cuadrado recorrer la matrix
	for(list<Cuadrado>::iterator itCua = lista_cuadrado.begin(); itCua!=lista_cuadrado.end(); ++itCua)
	{
		std::cout<<"Cuadrado"<<std::endl;
		for(int i=0;i<nfilas;i++)
		{
			for(int j=0; j<M;j++)
			{
				if( (*itCua).pertenece(i+ajuste,j) && ((*itCua).pertenece(pre->getX(),pre->getY())) )
				{//si la celda pertenece al cuadrado y ademas el cuadrado contiene al depredador
					matrix[i][j].aumentar();
				}
			}
		}
		for(int i=0;i<nfilas;i++)
		{
			for(int j=0; j<M;j++)
			{
				std::cout<<matrix[i][j].getAltura()<<",";
			}
			std::cout<<std::endl;
		}
	}
	
	//para cada cuadrado recorrer la matrix
	for(list<Cuadrado>::iterator itCua = lista_cuadrado.begin(); itCua!=lista_cuadrado.end(); ++itCua)
	{
		for(int i=0;i<nfilas;i++)
		{
			for(int j=0; j<M;j++)
			{
				if( (*itCua).pertenece(i+ajuste,j) && !((*itCua).pertenece(pre->getX(),pre->getY())) )
				{//si la celda pertenece al cuadrado y ademas el cuadrado NO contiene al depredador
					matrix[i][j].setAltura(-1);
				}
			}
		}
	}
	
	std::cout<<"final"<<std::endl;
	for(int i=0;i<nfilas;i++)
	{
		for(int j=0; j<M;j++)
		{
			std::cout<<matrix[i][j].getAltura()<<",";
		}
		std::cout<<std::endl;
	}
	std::cout<<"B"<<std::endl;
	return 0;
}






