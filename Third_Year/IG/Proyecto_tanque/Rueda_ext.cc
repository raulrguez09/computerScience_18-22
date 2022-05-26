#include "Rueda_ext.h"

// *****************************************************************************
//
// Clase Rueda_ext.cc
//
// *****************************************************************************

Rueda_ext::Rueda_ext(){
       rueda_ext = new Cilindro(9, 50, 20, 5, 'z', 1);
       cyan_plastic = Material({ 0.0,0.1,0.06 ,1.0}, { 0.0,0.50980392,0.50980392,1.0}, {0.50196078,0.50196078,0.50196078,1.0 }, 32.0);
}

void Rueda_ext::setMaterial(){
    rueda_ext->setMaterial(cyan_plastic);
}
void Rueda_ext::draw(unsigned int modo, bool modoLuz, unsigned int color,  bool ajedrez, bool tapaSup, bool tapaInf){
        glPushMatrix();
            rueda_ext->draw(modo, modoLuz, color, ajedrez, tapaSup, tapaInf);
        glPopMatrix();
}
