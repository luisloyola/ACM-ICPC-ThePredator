CC = mpicxx
FLAGS = -std=c++11 -Wall -g

ZIP = 18018294-2_17832733-k.zip

EXE = lab2
VPATH = src


## compilacion de fuentes

ALL: $(EXE)

$(EXE): Area.o Celda.o Cuadrado.o Graph.o mainleer.o Predator.o comunicacion.o
	$(CC) -o $@ $^ $(FLAGS)

%.o: %.cpp
	$(CC) -c $< -o $@ $(FLAGS)


## dependencias

Area.o: Area.hpp
Celda.o: Celda.hpp
Cuadrado.o: Cuadrado.hpp
Graph.o: Graph.hpp
Predator.o: Predator.hpp
mainleer.o: Area.hpp Celda.hpp comunicacion.hpp Cuadrado.hpp Graph.hpp Predator.hpp
comunicacion.o: comunicacion.hpp Area.hpp Cuadrado.hpp Predator.hpp

## programa prueba

test: main_prueba.o
	$(CC) -o $@ $^ $(FLAGS)


## generar zip de salida el cual se sube a www.usachvirtual.cl

archive: $(ZIP)

$(ZIP): src/*.cpp src/*.hpp
	git archive MPI --prefix=lab2/ --format=zip > $@



clean:
	rm *.o -f
	rm $(EXE) -f
