// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Ruedas_int_dcha.h

//
// #############################################################################

#ifndef Ruedas_int_dcha_H_INCLUDED
#define Ruedas_int_dcha_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "objrevolucion.h"
#include "cilindro.h"

class Ruedas_int_dcha : public Malla3D{
    protected:
        Cilindro * ruedas_int_dcha1 = nullptr;
        Cilindro * ruedas_int_dcha2 = nullptr; 
        Cilindro * ruedas_int_dcha3 = nullptr; 
        Cilindro * ruedas_int_dcha4 = nullptr; 
        Cilindro * ruedas_int_dcha5 = nullptr; 
        Cilindro * ruedas_int_dcha6 = nullptr; 
        Cilindro * ruedas_int_dcha7 = nullptr;
        Cilindro * ruedas_int_dcha8 = nullptr; 
        Cilindro * ruedas_int_dcha9 = nullptr;
        Material yellow_plastic; 

    public:
        Ruedas_int_dcha();
        void setMaterial();
        void draw(unsigned int modo, bool modoLuz, unsigned int color, bool ajedrez, bool tapaSup, bool tapaInf);
};

#endif