/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "GestorFiltros.h"

GestorFiltros::GestorFiltros(){
    FiltroTiempo * f1 = new FiltroTiempo();
    FiltroPersonas * f2 = new FiltroPersonas();
    FiltroIva * f3 = new FiltroIva();

    cadenaFiltros.addFiltro(f1);
    cadenaFiltros.addFiltro(f2);
    cadenaFiltros.addFiltro(f3);
}

void GestorFiltros::filtrar(Alquiler & alq){
    cadenaFiltros.ejecutar(alq);
}

void GestorFiltros::setFiltro(Filtro * f){
    cadenaFiltros.addFiltro(f);
}