/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "FiltroPersonas.h"
#include "Alquiler.h"

void FiltroPersonas::ejecutar(Alquiler &alq){
    string deporte = alq.getDeporte();
    int n_personas = alq.getPersonas();
    float coste = alq.getPrecio();

    if((deporte == "Volleyball" && n_personas == 12) || (deporte == "Futbol" && n_personas == 11) 
    || (deporte == "Baloncesto" && n_personas == 10)){
        coste -= coste * descuento;
    }
    
    alq.setPrecio(coste);
}