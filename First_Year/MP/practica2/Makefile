#DEFINIMOS LOS MACROS DE LAS CARPETAS

BIN=./bin
OBJ=./obj
SRC=./src
INC=./include
ZIP=./zip
DOC=./doc
PRC=practica2

all: $(BIN)/intervalo

$(BIN)/intervalo: $(OBJ)/intervalo.o $(OBJ)/main.o
	g++ $(OBJ)/intervalo.o $(OBJ)/main.o -o $(BIN)/intervalo

$(OBJ)/intervalo.o: $(SRC)/intervalo.cpp $(INC)/intervalo.h
	g++ -c $(SRC)/intervalo.cpp -o $(OBJ)/intervalo.o -I$(INC)

$(OBJ)/main.o: $(SRC)/main.cpp $(INC)/intervalo.h
	g++ -c $(SRC)/main.cpp -o $(OBJ)/main.o -I$(INC)

clean: 
	@echo "LIMPIANDO..."
	rm -rf $(OBJ)/*.o $(BIN)/* $(DOC)/latex $(DOC)/html

zip: clean
	@echo "GENERANDO ZIP DEL PROYECTO: " $(PRC)
	zip -r $(ZIP)/$(PRC).zip *

doxy:
	doxygen $(DOC)/intervalo.doxy

