CC=g++

INCLUDE_DIR= ./include

LIB_DIR= ./lib

BIN= bin

SRC= src

DOC= doc

OBJ= obj

all: circulomedio 

circulomedio: central.o circulo.o punto.o libformas.a
	$(CC) -L$(LIB_DIR) -o $(BIN)/$@ $(OBJ)/circulo.o $(OBJ)/punto.o $(OBJ)/central.o -lformas

central.o: $(SRC)/central.cpp $(INCLUDE_DIR)/punto.h $(INCLUDE_DIR)/circulo.h
	$(CC) -I$(INCLUDE_DIR) -c $< -o $(OBJ)/$@

circulo.o: $(SRC)/circulo.cpp $(INCLUDE_DIR)/punto.h $(INCLUDE_DIR)/circulo.h
	$(CC) -I$(INCLUDE_DIR) -c $< -o $(OBJ)/$@

punto.o: $(SRC)/punto.cpp $(INCLUDE_DIR)/punto.h
	$(CC) -I$(INCLUDE_DIR) -c $< -o $(OBJ)/$@

libformas.a: circulo.o punto.o
	ar rsv $(LIB_DIR)/$@ $(OBJ)/circulo.o $(OBJ)/punto.o

clean:
	@echo "Limpiando..."
	rm $(OBJ)/*.o $(LIB_DIR)/*.a $(BIN)/* -r $(DOC)/*

doxy:
	doxygen $(DOC)/circulomedio.doxy
