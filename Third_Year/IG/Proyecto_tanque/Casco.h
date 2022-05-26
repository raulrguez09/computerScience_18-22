// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Casco.h

//
// #############################################################################

#ifndef CASCO_H_INCLUDED
#define CASCO_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "objrevolucion.h"
#include "esfera.h"

class Casco : public Malla3D{
    protected:
        Esfera * casco = nullptr;
        Material verde_plastico;
    public:
        Casco();
        void setMaterial();
        void draw(unsigned int modo, bool modoLuz, unsigned int color, bool ajedrez, bool tapaSup, bool tapaInf);
};

#endif