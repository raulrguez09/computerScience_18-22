#include "Casco.h"

// *****************************************************************************
//
// Clase Casco.cc
//
// *****************************************************************************

Casco::Casco(){
    casco = new Esfera(9, 100, false, 20, 'y');
    verde_plastico = Material({0.0,0.0,0.0,1.0}, {0.1,0.35,0.1,1.0}, {0.45,0.55,0.45,1.0 }, 32.0);
}

void Casco::setMaterial(){
    casco->setMaterial(verde_plastico);
}

void Casco::draw(unsigned int modo, bool modoLuz, unsigned int color,  bool ajedrez, bool tapaSup, bool tapaInf){
        glPushMatrix();
            casco->draw(modo, modoLuz, color, ajedrez, tapaSup, tapaInf);
        glPopMatrix();
}
