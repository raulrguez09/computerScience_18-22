/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Alquiler.h
 * Author: raulrguez
 *
 * Created on 4 de abril de 2021, 10:17
 */

#ifndef ALQUILER_H
#define ALQUILER_H
#include "iostream"
using namespace std;

class Alquiler{
    private:
        float precio;
        string deporte;
        int tiempo;
        int n_personas;
    
    public:
        string getDeporte();
        int getTiempo();
        float getPrecio();
        int getPersonas();
        
        void setDeporte(string dep);
        void setTiempo(int tmp);
        void setPrecio(float coste);
        void setPersonas(int n);
        void setAlquiler(float coste, string dep, int tmp, int n);
};

#endif /* ALQUILER_H */

