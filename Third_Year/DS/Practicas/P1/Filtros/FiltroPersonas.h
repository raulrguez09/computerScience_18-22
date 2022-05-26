/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FiltroPersonas.h
 * Author: raulrguez
 *
 * Created on 4 de abril de 2021, 10:17
 */

#ifndef FILTROPERSONAS_H
#define FILTROPERSONAS_H

#include "Alquiler.h"
#include "Filtro.h"
#include <iostream>
using namespace std;

class FiltroPersonas : public Filtro{
    private:
        float descuento = 0.1;
    public:
        void ejecutar(Alquiler &alq);
};

#endif /* FILTROPERSONAS_H */

