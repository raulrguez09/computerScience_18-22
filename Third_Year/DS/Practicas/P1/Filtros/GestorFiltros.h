/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GestorFiltros.h
 * Author: raulrguez
 *
 * Created on 4 de abril de 2021, 10:15
 */

#ifndef GESTORFILTROS_H
#define GESTORFILTROS_H

#include <iostream>
#include "FiltroIva.h"
#include "FiltroPersonas.h"
#include "FiltroTiempo.h"
#include "Alquiler.h"
#include "CadenaFiltro.h"
using namespace std;

class GestorFiltros{
    private:
        CadenaFiltro cadenaFiltros;
    public:
        GestorFiltros();
        void filtrar(Alquiler & alq);
        void setFiltro(Filtro * f);
};

#endif /* GESTORFILTROS_H */

