#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Cuadrado.cpp"

 
//using namespace std;
 
int main(int argc, char* argv[])
{
	/*
	bsp_begin( bsp_nprocs() );
   
	int proc = bsp_nprocs();
	int pid  = bsp_pid();

	ifstream file(argv[1]); // pass file name as argment
	string linebuffer;
 
	while (file && getline(file, linebuffer)){
	if (linebuffer.length() == 0)continue;
		 // do something
	 	cout << linebuffer << endl;
	}
	*/
	
	//testear cuadrados
	cuadrado* cua = malloc(sizeof (cuadrado));
	cua->x = 3;
	cua->y = 2;
	cua->size = 4;
	printf ("%d\n", pertenece(4,4,cua));
	
	
	return 0;
}
