/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "CadenaFiltro.h"

void CadenaFiltro::addFiltro(Filtro * f){
    filtros.push_back(f);
}

void CadenaFiltro::ejecutar(Alquiler & alq){
    for(int i = 0; i < filtros.size(); i++){
        filtros[i]->ejecutar(alq);
    }
}