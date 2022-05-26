#include "Canon.h"

// *****************************************************************************
//
// Clase Canon.cc
//
// *****************************************************************************

Canon::Canon(){
    canon = new Cilindro(9, 50, 20, 5, 'x', 0);
    red_plastic = Material({0.0,0.0,0.0,1.0}, {0.5,0.0,0.0,1.0}, {0.7,0.6,0.6,1.0}, 32.0);
}
void Canon::setMaterial(){
    canon->setMaterial(red_plastic);
}

void Canon::draw(unsigned int modo, bool modoLuz, unsigned int color,  bool ajedrez, bool tapaSup, bool tapaInf){
        glPushMatrix();
            canon->draw(modo, modoLuz, color, ajedrez, tapaSup, tapaInf);
        glPopMatrix();
}
