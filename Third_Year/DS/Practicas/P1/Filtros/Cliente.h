/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cliente.h
 * Author: raulrguez
 *
 * Created on 4 de abril de 2021, 10:44
 */

#ifndef CLIENTE_H
#define CLIENTE_H



#include <iostream>
#include "Alquiler.h"
using namespace std;

class Cliente{
    private:
        Alquiler alquiler;
    public:
        Cliente();
        Alquiler getAlquiler();
        void setAlquiler(Alquiler alq);
};

#endif /* CLIENTE_H */

