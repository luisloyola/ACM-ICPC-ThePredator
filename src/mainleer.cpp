#include <fstream>
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include "Cuadrado.hpp"
#include "Predator.hpp"
#include "Area.hpp"
#include "Celda.hpp"
#include "Graph.hpp"

#define M 10

using namespace std;

int main(int argc, char** args)
{
///SS0:
	int C, Q;	//C=número de cuadrados, Q=número de predators.
	ifstream in(args[1]);	//archivo de entrada.
	
	if (!in.is_open())
	{
		cerr<< "No se encontro el archivo "<< args[1]<< endl;
		return 1;
	}

	//Leer archivo y recuperar argumentos
	in >> C;
	list<Cuadrado> lista_cuadrado;
	for(int i=0;i<C;i++)
	{//para cada cuadrado
		int r,c,s;
		in >> r >> c >> s;
		//cout << "r:" << r << " c:" << c << " s:" << s <<endl;
		Cuadrado cua_aux = Cuadrado(r-1,c-1,s);	//crear un cuadrado en el stack
		lista_cuadrado.push_back(cua_aux);			//copia ese cuadrado en una lista
	}
	in >> Q;
	list<Predator> lista_predator;
	for(int i=0; i<Q;i++)
	{//para cada predator
		int pr,pc;
		in >> pr >>pc;
		//cout<< "pr:" << pr << " pc:" << pc << endl;
		Predator pre_aux =  Predator(pr-1,pc-1);	//crear un depredador en el stack
		lista_predator.push_back(pre_aux);			//copia ese predador en una lista
	}
	
	
//////TESTING
/*
	cout<<"TESTING:"<<endl;
	//Una forma de recorrer la lista con iteradores
	list<Cuadrado>::iterator itCua;
	itCua=lista_cuadrado.begin();
	for(int i=0;i<C;i++)
	{
		cout<< (*itCua).getX()<<"-"<<(*itCua).getY()<<"-"<<(*itCua).getLargo() <<endl;
		itCua++;
	}
	
	//otra forma de recorrer lista con iteradores.
	for(list<Predator>::iterator itPre = lista_predator.begin(); itPre!=lista_predator.end(); ++itPre)
	{
		cout<< (*itPre).getX()<<"-"<<(*itPre).getY()<<endl;
	}
	cout<<"END_TESTING"<<endl;
*/
//////endTESTING
	
	///P0 hace broadcast de la lista de cuadrados y la posición de un predator
///SS1:
	//Cada maquina tiene que asignar su espacio de memoria
	int P=4;		//número de procesos a usar
	int pid=3;		//Id de cada procesador.
	Predator pre = Predator(9,4);
	
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
					((*itCua).pertenece(pre.getX(),pre.getY()))) 
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
				  !((*itCua).pertenece(pre.getX(),pre.getY())) )
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
			cout<<"X:"<<matrix[i][j].getX()<<" Y:"<<matrix[i][j].getY()<<endl;
		}
	}
	//Area* A = new Area();
	//(*A).add_celda_sup2(&(matrix[3][9]));
	//cout<<"asdf:"<<(*A).get_sup().front().getX()<<endl;
////ENDTesting

	//generar lista de áreas
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
				int aux = A.recorrerArea(i, j, matrix, nfilas, M, valor_predator, pre);
				A.setArea(aux);
				LArea.push_back(A);
			}
		}
	}
	
	
	for(int i=0;i<nfilas;i++){
		for(int j=0; j<M;j++){
			cout<<"X:"<<matrix[i][j].getX()<<" Y:"<<matrix[i][j].getY()<<endl;
		}
	}
	
/////MOSTRAR valores de area
	for(auto& itA:LArea)
	{
		cout<<"Tamaño del area: "<<itA.getArea()<<endl;
		cout<<"Contiene predator:"<<itA.contiene_predator<<endl;
		cout<<"Sup:"<<endl;
		for(auto& itS:itA.get_sup())
		{
			cout<<"X: "<<itS.getX()<<" Y:"<<itS.getY()<<endl;
		}
		cout<<"Inf:"<<endl;
		for(auto& itI:itA.get_inf())
		{
			cout<<"X: "<<itI.getX()<<" Y:"<<itI.getY()<<endl;
		}
	}
////END_MOSTRAR

////TESTING
/*
	Area A_TEST;
	Celda C_TEST;
	C_TEST.setXY(5,4);
	A_TEST.add_celda_sup2(C_TEST);
	A_TEST.setArea(6);
	LArea.push_back(A_TEST);
	*/
/////END_TESTING
	//Matching the areas
	Graph g = Graph(LArea.size());
	int i=0;
	int j=0;
	int index_area_con_predator=-1;
	for(auto& A:LArea)
	{
		j=0;
		if(A.contiene_predator)
		{
			index_area_con_predator = i;
		}
		for(auto& B:LArea)
		{
			if(A.es_adyacente(B))
			{
				g.addEdge(i,j);
				cout<<i<<" es adyacente a "<<j<<endl;
			}
			j++;
		}
		i++;
	}
	
	
////TESTING
/*
	g.addEdge(0,3);
	g.addEdge(3,2);
	index_area_con_predator=2;
	*/
////END_TESTING
	//identificar que areas son adyacentes transitivamente con el area que contiene al predator.
	bool* ar = new bool[LArea.size()];//arreglo del tamaño de la lista de areas
	for(unsigned int a=0; a<LArea.size();a++){
		ar[a]=false;
	}
	g.flood(index_area_con_predator,ar);	//ar dice a que areas puede llegar el predator
	
	//Sumar las areas
	int areaTotal=0;
	i=0;
	for(auto& A:LArea){
	
		if(ar[i])
		{//si el predator puede llegar a esta area
			areaTotal += A.getArea();
		}
		i++;
	}
	cout<<"El area es:"<<areaTotal<<endl;
	

	return 0;
}






