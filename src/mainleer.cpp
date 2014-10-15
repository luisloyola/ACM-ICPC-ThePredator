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

	int C, Q;	//C=número de cuadrados, Q=número de predators.
	ifstream in(args[1]);	//archivo de entrada.
	
	if (!in.is_open())
	{
		cerr<< "No se encontro el archivo "<< args[1]<< endl;
		return 1;
	}

	//Leer archivo y recuperar argumentos
	in >> C;
	std::list<Cuadrado> lista_cuadrado;
	for(int i=0;i<C;i++)
	{//para cada cuadrado
		int r,c,s;
		in >> r >> c >> s;
		//std::cout << "r:" << r << " c:" << c << " s:" << s <<std::endl;
		Cuadrado* cua_aux = new Cuadrado(r-1,c-1,s);	//crear un cuadrado en el heap
		lista_cuadrado.push_back(*cua_aux);			//guardar ese cuadrado en una lista
	}
	in >> Q;
	std::list<Predator> lista_predator;
	for(int i=0; i<Q;i++)
	{//para cada predator
		int pr,pc;
		in >> pr >>pc;
		//std::cout<< "pr:" << pr << " pc:" << pc << std::endl;
		Predator* pre_aux = new Predator(pr-1,pc-1);	//crear un depredador en el heap
		lista_predator.push_back(*pre_aux);			//guardar ese predador en una lista
	}
	
	
//////TESTING
/*
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
*/
//////endTESTING


	//Cada maquina tiene que asignar su espacio de memoria
	int P=4;		//número de procesos a usar
	int pid=3;		//Id de cada procesador.
	Predator* pre = new Predator(5,5);
	
	//Crear matriz dinamica de Celdas.
	Celda** matrix = NULL;
	int nfilas;
	if(pid==P-1)//último proceso
	{
		nfilas = M-(M/P*(P-1));		//el último proceso tiene todas las filas que quedan. 
	}else{//cualquier otro proceso
		nfilas = M/P;				//franjas de la matriz total de M/P
	}
	matrix = new Celda*[nfilas];
	for(int i =0; i<nfilas;i++)
	{
		matrix[i] = new Celda[M];
	}

	//Inicializar matriz con celdas de altura 0 y asignar sus posiciones X e Y
	int ajuste = M/P*pid;	//cada proceso tiene una franja de la matriz total, por lo que matrix[0][0] de P1 sería matrix[M/P][0]
	for(int i=0;i<nfilas;i++)
	{
		for(int j=0; j<M;j++)
		{
			matrix[i][j].setAltura(0);
			matrix[i][j].setXY(i+ajuste,j);
		}
	}


	//Recorrer matrix de celdas (Cuadrados que contienen al predator)
	
	//para cada cuadrado recorrer la matrix
	for(list<Cuadrado>::iterator itCua = lista_cuadrado.begin(); itCua!=lista_cuadrado.end(); ++itCua)
	{
		for(int i=0;i<nfilas;i++)
		{
			for(int j=0; j<M;j++)
			{
				if( (*itCua).pertenece(matrix[i][j].getX(),matrix[i][j].getY()) &&
					((*itCua).pertenece(pre->getX(),pre->getY()))) 
				{//si la celda pertenece al cuadrado y ademas el cuadrado contiene al depredador
					matrix[i][j].aumentar();
				}
			}
		}
	}
	
	
	//para cada cuadrado recorrer la matrix (Cuadrados que NO contienen al predator)
	for(list<Cuadrado>::iterator itCua = lista_cuadrado.begin(); itCua!=lista_cuadrado.end(); ++itCua)
	{
		for(int i=0;i<nfilas;i++)
		{
			for(int j=0; j<M;j++)
			{
				if( (*itCua).pertenece(matrix[i][j].getX(), matrix[i][j].getY()) && 
				  !((*itCua).pertenece(pre->getX(),pre->getY())) )
				{//si la celda pertenece al cuadrado y ademas el cuadrado NO contiene al depredador
					matrix[i][j].setAltura(-1);
				}
			}
		}
	}
	
//////TESTING
	int test1 = 3;
	for(int i=0; i<nfilas;i++){
		for(int j=0;j<M;j++){
			matrix[i][j].setAltura(0);
		}
	}
	matrix[0][0].setAltura(test1);
	matrix[0][1].setAltura(test1);
	matrix[1][0].setAltura(test1);
	
	matrix[2][1].setAltura(test1);
	matrix[3][0].setAltura(test1);
	matrix[3][1].setAltura(test1);
	matrix[3][2].setAltura(test1);
	matrix[3][3].setAltura(test1);
	matrix[3][4].setAltura(test1);
	matrix[2][4].setAltura(test1);
	matrix[1][4].setAltura(test1);
	matrix[0][4].setAltura(test1);
	matrix[0][5].setAltura(test1);

	matrix[2][6].setAltura(test1);
	matrix[2][7].setAltura(test1);
	matrix[2][8].setAltura(test1);
	matrix[1][7].setAltura(test1);
	
	matrix[3][9].setAltura(test1);
	for(int i=0;i<nfilas;i++){
		for(int j=0; j<M;j++){
			std::cout<<"X:"<<matrix[i][j].getX()<<" Y:"<<matrix[i][j].getY()<<std::endl;
		}
	}
	//Area* A = new Area();
	//(*A).add_celda_sup2(&(matrix[3][9]));
	//std::cout<<"asdf:"<<(*A).get_sup().front().getX()<<std::endl;
////ENDTesting

	//generar áreas
	int valor_predator = test1;	///TESTING///
	//int valor_predator = 3;
	list<Area> LArea;
	for(int i=0; i<nfilas; i++)
	{
		for(int j=0; j<M;j++)
		{
			if( (!matrix[i][j].esVisitada()) && matrix[i][j].getAltura()==valor_predator)
			{//si la celda no ha sido visitada y está a la altura del predator
				//Area* A = new Area();
				Area A;
				int aux = A.recorrerArea(i, j, matrix, nfilas, M, valor_predator);
				A.setArea(aux);
				LArea.push_back(A);
			}
		}
	}
	
	
	for(int i=0;i<nfilas;i++){
		for(int j=0; j<M;j++){
			std::cout<<"X:"<<matrix[i][j].getX()<<" Y:"<<matrix[i][j].getY()<<std::endl;
		}
	}
	std::cout<<"numero de areas:"<<LArea.size()<<std::endl;
	for(list<Area>::iterator itA = LArea.begin(); itA != LArea.end(); ++itA)
	{
		std::cout<<"	AREA mide: "<<(*itA).getArea()<<std::endl;
		std::cout<<"	Superiores:"<<std::endl;
		std::cout<<"	"<<(*itA).get_sup().size()<<std::endl;
		for(list<Celda>::iterator itCSup = (*itA).get_sup().begin(); itCSup != (*itA).get_sup().end();){
			std::cout<<"		ASDF"<<std::endl;
			std::cout<<"X:"<<(*itCSup).getX()<<" Y:"<<(*itCSup).getY()<<std::endl;
			itCSup++;
		}
		std::cout<<"	qwerty"<<std::endl;
		//std::cout<<"Inferiores:"<<std::endl;
		//for(list<Celda>::iterator itCInf = (*itA).get_inf().begin(); itCInf != (*itA).get_inf().end(); ++itCInf){
			//std::cout<<"X:"<<(*itCInf).getX()<<" Y:"<<(*itCInf).getY()<<std::endl;
		//}
	}
	return 0;
}






