#include <fstream>
#include <iostream>
#include <string>
#include <list>
#include "Cuadrado.cpp"
#include "Predator.cpp"

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
		Cuadrado* cua_aux = new Cuadrado(r,c,s);	//crear un cuadrado en el heap
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
		Predator* pre_aux = new Predator(pr,pc);	//crear un depredador en el heap
		lista_predator.push_back(*pre_aux);			//guardar ese predador en una lista
	}
	
	
	//TESTING
	std::cout<<"TESTING:"<<std::endl;
	list<Cuadrado>::iterator itCua;
	itCua=lista_cuadrado.begin();
	for(int i=0;i<C;i++)
	{
		std::cout<< (*itCua).getX()<<"-"<<(*itCua).getY()<<"-"<<(*itCua).getLargo() <<std::endl;
		itCua++;
	}
	//endTESTING
	return 0;
}
