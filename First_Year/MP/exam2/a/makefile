COMP=g++
CPPFLAGS=-g -Wall
EXEC=ejercicio3

$(EXEC): Functions.o ArrayProc.o Main.o
	$(COMP) -o $@ $^
Main.o: Main.cpp Functions.hpp ArrayProc.hpp
	$(COMP) $(CPPFLAGS) -c $<
Functions.o: Functions.cpp Functions.hpp
	$(COMP) $(CPPFLAGS) -c $<
ArrayProc.o: ArrayProc.cpp ArrayProc.hpp
	$(COMP) $(CPPFLAGS) -c $<
touch: 
	touch *.?pp
clear: 
	rm *.o $(EXEC)
