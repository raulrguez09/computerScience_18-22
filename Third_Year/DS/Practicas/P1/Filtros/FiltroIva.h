/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FiltroIva.h
 * Author: raulrguez
 *
 * Created on 4 de abril de 2021, 10:16
 */

#ifndef FILTROIVA_H
#define FILTROIVA_H

#include "Alquiler.h"
#include "Filtro.h"

class FiltroIva : public Filtro{
    private:
        float IVA = 0.21;
    public:
        void ejecutar(Alquiler &alq);
};

#endif /* FILTROIVA_H */

