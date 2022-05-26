#include <iostream>
#include <cmath> 
#include "punto.h"
using namespace std; 

void Punto::setX(double nuevoX)  {
	x = nuevoX;
}

void Punto::setY(double nuevoY)  {
	y = nuevoY;
}
 
 
void Punto::escribir() const{
    cout << "(" << x << "," << y << ")" << endl;
}


void Punto::leer(){
    // Formato de lectura del punto: (x,y)
    char car;
    cin >> car >> x >> car >> y >> car;
}

/// Clase Punto

double distancia(Punto p1, Punto p2){
    return sqrt((p1.getX()-p2.getX())*(p1.getX()-p2.getX()) +
         (p1.getY()-p2.getY())*(p1.getY()-p2.getY()));
}

Punto puntoMedio(Punto p1, Punto p2){
    Punto pMedio;
    pMedio.setX((p1.getX()+p2.getX())/2.0);
    pMedio.setY((p1.getY()+p2.getY())/2.0);
    return pMedio;
}

