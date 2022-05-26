/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "FiltroIva.h"
#include "Alquiler.h"

void FiltroIva::ejecutar(Alquiler &alq){
    float precio = alq.getPrecio();
    precio += precio*IVA;
    alq.setPrecio(precio);
}