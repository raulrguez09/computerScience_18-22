/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   FiltroTiempo.h
 * Author: raulrguez
 *
 * Created on 4 de abril de 2021, 10:16
 */

#ifndef FILTROTIEMPO_H
#define FILTROTIEMPO_H

#include "Alquiler.h"
#include "Filtro.h"

class FiltroTiempo : public Filtro{
    private:
        int min = 15;
    
    public:
        void ejecutar(Alquiler & alq);
};

#endif /* FILTROTIEMPO_H */

