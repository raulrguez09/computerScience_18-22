#include <iostream>
#include "intervalo.h"

using namespace std;


int main(){
    const int CAPACIDAD = 10;
    int i, nintervalos;
    Intervalo interv[CAPACIDAD];
    Intervalo inter;
    
    cout << "Cuantos intervalos (max 10):";
    do{
        cin >> nintervalos;
    } while (nintervalos >10);
    
    cout << "Introduce [ o ( cotaInferior, cotaSuperior ) o ]";
    for(i=0; i < nintervalos; i++)
        leer(interv[i]);
	
	inter=interv[0];
    for(i=0; i<nintervalos-1; i++){
    	inter=Interseccion(inter,interv[i+1]);
	}
	
	escribir(inter);
	
	cout << endl;
	
	
	return 0;
    
}
