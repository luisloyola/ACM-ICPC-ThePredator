CC = mpicxx
FLAGS = -std=c++11 -Wall

ZIP = LAB2_18018294-2_17832733-k.zip

EXE = lab2
VPATH = src


## compilacion de fuentes

ALL: $(EXE)

$(EXE): Area.o Celda.o Cuadrado.o Graph.o main.o Predator.o comunicacion.o
	$(CC) -o $@ $^ $(FLAGS)

%.o: %.cpp
	$(CC) -c $< -o $@ $(FLAGS)


## dependencias

Area.o: Area.hpp
Celda.o: Celda.hpp
Cuadrado.o: Cuadrado.hpp Predator.hpp
Graph.o: Graph.hpp
Predator.o: Predator.hpp
main.o: Area.hpp Celda.hpp comunicacion.hpp Cuadrado.hpp Graph.hpp Predator.hpp
comunicacion.o: comunicacion.hpp Area.hpp Cuadrado.hpp Predator.hpp

## programa prueba

test: main_prueba.o Area.o Celda.o Cuadrado.o Graph.o  Predator.o comunicacion.o
	$(CC) -o $@ $^ $(FLAGS)


## generar zip de salida el cual se sube a www.usachvirtual.cl

archive: $(ZIP)

$(ZIP): src/*.cpp src/*.hpp Makefile
	git archive MPI --prefix=lab2/ --format=zip > $@ 

clean:
	rm *.o -f
	rm $(EXE) -f
