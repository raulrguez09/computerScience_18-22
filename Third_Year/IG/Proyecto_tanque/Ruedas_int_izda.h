// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Ruedas_int_izda.h

//
// #############################################################################

#ifndef Ruedas_int_izda_H_INCLUDED
#define Ruedas_int_izda_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "objrevolucion.h"
#include "cilindro.h"

class Ruedas_int_izda : public Malla3D{
    protected:
        Cilindro * ruedas_int_izda1 = nullptr;
        Cilindro * ruedas_int_izda2 = nullptr; 
        Cilindro * ruedas_int_izda3 = nullptr; 
        Cilindro * ruedas_int_izda4 = nullptr; 
        Cilindro * ruedas_int_izda5 = nullptr; 
        Cilindro * ruedas_int_izda6 = nullptr; 
        Cilindro * ruedas_int_izda7 = nullptr;
        Cilindro * ruedas_int_izda8 = nullptr; 
        Cilindro * ruedas_int_izda9 = nullptr;
        Material yellow_plastic;  

    public:
        Ruedas_int_izda();
        void setMaterial();
        void draw(unsigned int modo, bool modoLuz, unsigned int color, bool ajedrez, bool tapaSup, bool tapaInf);
};

#endif