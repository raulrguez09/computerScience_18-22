// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: BaseTanque.h

//
// #############################################################################

#ifndef BASETANQUE_H_INCLUDED
#define BASETANQUE_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "cubo.h"

class BaseTanque : public Malla3D{
    protected:
        Cubo * base = nullptr;
        Material red_plastic;;
    public:
        BaseTanque();
        void setMaterial();
        void draw(unsigned int modo, bool modoLuz, unsigned int color,  bool ajedrez);
};

#endif