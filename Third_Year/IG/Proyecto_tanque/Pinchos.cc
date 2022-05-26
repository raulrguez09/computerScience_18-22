#include "Pinchos.h"

// *****************************************************************************
//
// Clase Pinchos.cc
//
// *****************************************************************************

Pinchos::Pinchos(){
    verde_plastico = Material({0.0,0.0,0.0,1.0}, {0.1,0.35,0.1,1.0}, {0.45,0.55,0.45,1.0 }, 32.0);
    pincho1 = new Tetraedro();
    pincho2 = new Tetraedro();
}

void Pinchos::setMaterial(){
    pincho1->setMaterial(verde_plastico);
    pincho2->setMaterial(verde_plastico);
}

void Pinchos::draw(unsigned int modo, bool modoLuz, unsigned int color,  bool ajedrez){
    //BASE PINCHO DCHA
    glPushMatrix();
        glTranslatef(76.0,14.0,0.0);
        glRotatef(180, 0.0f, 1.0f, 0.0f);
        glRotatef(180, 1.0f, 0.0f, 0.0f);
        glScalef(1.0, 0.5, 1.0);
        pincho1->draw(modo, modoLuz, color, ajedrez);
    glPopMatrix();  

    //BASE PINCHO IZDA
    glPushMatrix();
        glTranslatef(-76.0,14.0,0.0);
        glRotatef(180, 1.0f, 0.0f, 0.0f);
        glScalef(1.0, 0.5, 1.0);
        pincho2->draw(modo, modoLuz, color, ajedrez);
    glPopMatrix();

}