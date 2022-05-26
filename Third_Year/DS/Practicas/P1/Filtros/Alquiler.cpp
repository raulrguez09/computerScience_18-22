/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "iostream"
using namespace std;
#include "Alquiler.h"


/***** METODOS GET *****/
float Alquiler::getPrecio(){
    return precio;
}

string Alquiler::getDeporte(){
    return deporte;
}

int Alquiler::getTiempo(){
    return tiempo;
}

int Alquiler::getPersonas(){
    return n_personas;
}

/***** METODOS GET *****/
void Alquiler::setPrecio(float coste){
    precio = coste;
}

void Alquiler::setDeporte(string dep){
    deporte = dep;
}

void Alquiler::setTiempo(int tmp){
    tiempo = tmp;
}

void Alquiler::setPersonas(int n){
    n_personas = n;    
}

void Alquiler::setAlquiler(float coste, string dep, int tmp, int n){
    precio = coste;
    deporte = dep;
    tiempo = tmp;
    n_personas = n;
}