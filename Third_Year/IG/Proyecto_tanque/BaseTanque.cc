#include "BaseTanque.h"

// *****************************************************************************
//
// Clase BaseTanque.cc
//
// *****************************************************************************

BaseTanque::BaseTanque(){
        base = new Cubo();
        red_plastic = Material({0.0,0.0,0.0,1.0}, {0.5,0.0,0.0,1.0}, {0.7,0.6,0.6,1.0}, 32.0);
}

void BaseTanque::setMaterial(){
        base->setMaterial(red_plastic);
}
void BaseTanque::draw(unsigned int modo, bool modoLuz, unsigned int color,  bool ajedrez){
        glPushMatrix();
                base->draw(modo, modoLuz, color, ajedrez);
        glPopMatrix();
}