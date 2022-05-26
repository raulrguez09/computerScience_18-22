/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Cliente.h"
#include <stdlib.h>
#include <time.h>

Cliente::Cliente(){
    
    string deportes[3] = {"Futbol","Baloncesto","Volleyball"};
    
    float precio_inicial = 5.0;
    int tiempo_alquiler = 20 + rand() % (121 - 20); //Entre 20 y 120 minutos
    int dep = rand() % 3;
    
    int numero_personas = 0;    
    if(dep == 0)
        numero_personas = 11 + rand() % (23 - 11); //Entre 11 y 22 personas
    else if(dep == 1)
        numero_personas = 5 + rand() % (11 - 5); //Entre 5 y 10 personas
    else if(dep == 2)
        numero_personas = 6 + rand() % (13 - 6); //Entre 6 y 12 personas
    
    alquiler.setAlquiler(precio_inicial,deportes[dep],tiempo_alquiler,numero_personas);
}

Alquiler Cliente::getAlquiler(){
    return alquiler;
}

void Cliente::setAlquiler(Alquiler alq){
    alquiler.setAlquiler(alq.getPrecio(),alq.getDeporte(),alq.getTiempo(),alq.getPersonas());
}