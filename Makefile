CC = g++
CFLAGS = -Wall -pthread

ZIP = LAB3_18018294-2_17832733-k.zip

EXE = lab3
VPATH = src


## compilacion de fuentes

ALL: $(EXE)

$(EXE): Area.o Celda.o Cuadrado.o Graph.o main.o Predator.o
	$(CC) -o $@ $^ $(CFLAGS)

%.o: %.cpp
	$(CC) -c $< -o $@ $(CFLAGS)


## dependencias

Area.o: Area.hpp
Celda.o: Celda.hpp
Cuadrado.o: Cuadrado.hpp Predator.hpp
Graph.o: Graph.hpp
Predator.o: Predator.hpp
main.o: Area.hpp Celda.hpp Cuadrado.hpp Graph.hpp Predator.hpp

## programa prueba

test: main_prueba.o
	$(CC) -o $@ $^ $(CFLAGS)


## generar zip de salida el cual se sube a www.usachvirtual.cl

archive: $(ZIP)

$(ZIP): src/*.cpp src/*.hpp Makefile
	git archive pthread --prefix=$(EXE)/ --format=zip > $@ 

clean:
	rm *.o -f
	rm $(EXE) -f
