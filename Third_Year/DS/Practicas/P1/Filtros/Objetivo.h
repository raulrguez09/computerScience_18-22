/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Objetivo.h
 * Author: raulrguez
 *
 * Created on 4 de abril de 2021, 15:39
 */

#ifndef OBJETIVO_H
#define OBJETIVO_H
#include "Alquiler.h"
#include "iostream"
#include <vector>
using namespace std;

class Objetivo{
    private:
        vector<Alquiler> alquileres;
    public:
        float calcularCosteMedio(vector<Alquiler> alq);
        float calcularTiempoMedio(vector<Alquiler> alq);
        void mostrarObjetivo();
        void nuevoAlquiler(Alquiler alq);
        vector<Alquiler> conseguirAlquileres(string deporte);
};

#endif /* OBJETIVO_H */

