/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CadenaFiltro.h
 * Author: raulrguez
 *
 * Created on 8 de abril de 2021, 11:02
 */

#ifndef CADENAFILTRO_H
#define CADENAFILTRO_H

#include "Filtro.h"
#include <vector>

class CadenaFiltro{
    private:
        vector<Filtro *> filtros;
    public:
        void addFiltro(Filtro * f);
        void ejecutar(Alquiler & alq);
};

#endif /* CADENAFILTRO_H */

