
#ifndef Pinchos_H_INCLUDED
#define Pinchos_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "tetraedro.h"

class Pinchos : public Malla3D{
    protected:
        Tetraedro * pincho1 = nullptr;
        Tetraedro * pincho2 = nullptr;
        Material verde_plastico;
    public:
        Pinchos();
        void setMaterial();
        void draw(unsigned int modo, bool modoLuz, unsigned int color,  bool ajedrez);
};

#endif