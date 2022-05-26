#include <iostream>
#include <cmath>
#include "circulo.h"
using namespace std;
/// Clase Círculo

Circulo::Circulo()  {
	centro.setX(0);
	centro.setY(0);
	radio = 0;
}

Circulo::Circulo(Punto centro, double radio)  {
	this->centro = centro;
	this->radio = radio;
	// set(centro,radio);
}

void Circulo::set(Punto centro, double radio)  {
	this->centro = centro;
	this->radio = radio;
}

Punto Circulo::getCentro() const  {
	return centro;
}

double Circulo::getRadio() const {
	return radio;
}

void Circulo::escribir() const{
    cout << radio << "-";
    centro.escribir();
}

void Circulo::leer(){
    // Formato de lectura del círculo: radio-(x,y)
    char car;

    cin >> radio;
    cin >> car; //Leer -
    centro.leer();
}

double Circulo::area() const{
    return M_PI*radio*radio;
}
/// Clase Circulo

double distancia (Circulo c1, Circulo c2){
    Punto centro1, centro2;
    double dist;

    centro1=c1.getCentro();
    centro2=c2.getCentro();
    dist=distancia(centro1,centro2)-c1.getRadio()-c2.getRadio();
    return dist;
}



bool interior (Punto p, Circulo c){
    if(distancia(p,c.getCentro())<=c.getRadio()) {
        return true;
    }
    else{
        return false;
    }
}

