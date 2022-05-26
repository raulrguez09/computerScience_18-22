/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Filtro.h
 * Author: raulrguez
 *
 * Created on 8 de abril de 2021, 11:02
 */

#ifndef FILTRO_H
#define FILTRO_H

#include "Alquiler.h"

class Filtro{
    public:
        virtual void ejecutar(Alquiler & alq){};
};



#endif /* FILTRO_H */

