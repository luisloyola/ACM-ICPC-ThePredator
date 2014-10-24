CC = mpicxx
FLAGS = -lbsponmpi -std=c++11 -Wall -g

BSP_INCLUDE_DIR = /usr/local/bsponmpi/include
BSP_LIB_DIR = /usr/local/bsponmpi/lib

ZIP = 18018294-2_17832733-k.zip

EXE = lab1
VPATH = src



## compilacion de fuentes

ALL: $(EXE)

$(EXE): Area.o Celda.o Cuadrado.o Graph.o mainleer.o Predator.o comunicacion.o
	$(CC) -I $(BSP_INCLUDE_DIR)  -o $@ $^ -L $(BSP_LIB_DIR) $(FLAGS)

%.o: %.cpp
	$(CC) -I $(BSP_INCLUDE_DIR) -c $< -o $@ -L $(BSP_LIB_DIR) $(FLAGS)


## dependencias

Area.o: Area.hpp
Celda.o: Celda.hpp
Cuadrado.o: Cuadrado.hpp
Graph.o: Graph.hpp
Predator.o: Predator.hpp
mainleer.o: Area.hpp Celda.hpp comunicacion.hpp Cuadrado.hpp Graph.hpp Predator.hpp
comunicacion.o: comunicacion.hpp Area.hpp Cuadrado.hpp Predator.hpp

## programa prueba

test: Area.o Celda.o Cuadrado.o Graph.o Predator.o main_prueba.o comunicacion.o
	$(CC) -I $(BSP_INCLUDE_DIR)  -o $@ $^ -L $(BSP_LIB_DIR) $(FLAGS)

main_prueba.o: Area.hpp Celda.hpp comunicacion.hpp Cuadrado.hpp Graph.hpp Predator.hpp

## generar zip de salida el cual se sube a www.usachvirtual.cl

archive: $(ZIP)

$(ZIP): src/*.cpp src/*.hpp
	git archive master --prefix=lab1/ --format=zip > $@



clean:
	rm *.o -f
	rm $(EXE) -f
