#DEFINIMOS LOS MACROS DE LAS CARPETAS

BIN=./bin
OBJ=./obj
SRC=./src
INC=./include
ZIP=./zip
DOC=./doc
PRC=ejercicio1

all: $(BIN)/utilidades

$(BIN)/utilidades: $(OBJ)/utilidades.o $(OBJ)/ejercicio1.o
	g++ $(OBJ)/utilidades.o $(OBJ)/ejercicio1.o -o $(BIN)/ejercicio1

$(OBJ)/utilidades.o: $(SRC)/utilidades.cpp $(INC)/utilidades.h
	g++ -c $(SRC)/utilidades.cpp -o $(OBJ)/utilidades.o -I$(INC)

$(OBJ)/ejercicio1.o: $(SRC)/ejercicio1.cpp $(INC)/utilidades.h
	g++ -c $(SRC)/ejercicio1.cpp -o $(OBJ)/ejercicio1.o -I$(INC)

clean: 
	@echo "LIMPIANDO..."
	rm -rf $(OBJ)/*.o $(BIN)/* $(DOC)/latex $(DOC)/html

zip: clean
	@echo "GENERANDO ZIP DEL PROYECTO: " $(PRC)
	zip -r $(ZIP)/$(PRC).zip *

doxy:
	doxygen $(DOC)/utilidades.doxy
