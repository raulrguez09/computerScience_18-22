// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Rueda_ext.h

//
// #############################################################################

#ifndef Rueda_ext_H_INCLUDED
#define Rueda_ext_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "objrevolucion.h"
#include "cilindro.h"

class Rueda_ext : public Malla3D{
    protected:
        Cilindro * rueda_ext = nullptr;
        Material cyan_plastic;
    public:
        Rueda_ext();
        void setMaterial();
        void draw(unsigned int modo, bool modoLuz, unsigned int color, bool ajedrez, bool tapaSup, bool tapaInf);
};

#endif