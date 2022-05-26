// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Canon.h

//
// #############################################################################

#ifndef Canon_H_INCLUDED
#define Canon_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "objrevolucion.h"
#include "cilindro.h"

class Canon : public Malla3D{
    protected:
        Cilindro * canon = nullptr;
        Material red_plastic;
    public:
        Canon();
        void setMaterial();
        void draw(unsigned int modo, bool modoLuz, unsigned int color, bool ajedrez, bool tapaSup, bool tapaInf);
};

#endif