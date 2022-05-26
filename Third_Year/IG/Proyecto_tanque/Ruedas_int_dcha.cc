#include "Ruedas_int_dcha.h"

// *****************************************************************************
//
// Clase Ruedas_int_dcha.cc
//
// *****************************************************************************

Ruedas_int_dcha::Ruedas_int_dcha(){
    ruedas_int_dcha1 = new Cilindro(9, 50, 20, 5, 'z', 0);
    ruedas_int_dcha2 = new Cilindro(9, 50, 20, 5, 'z', 0);
    ruedas_int_dcha3 = new Cilindro(9, 50, 20, 5, 'z', 0);
    ruedas_int_dcha4 = new Cilindro(9, 50, 20, 5, 'z', 0);
    ruedas_int_dcha5 = new Cilindro(9, 50, 20, 5, 'z', 0);
    ruedas_int_dcha6 = new Cilindro(9, 50, 20, 5, 'z', 0);
    ruedas_int_dcha7 = new Cilindro(9, 50, 20, 5, 'z', 0);
    ruedas_int_dcha8 = new Cilindro(9, 50, 20, 5, 'z', 0);
    ruedas_int_dcha9 = new Cilindro(9, 50, 20, 5, 'z', 0);
    yellow_plastic = Material({0.0,0.0,0.0,1.0 }, {0.5,0.5,0.0,1.0 }, {0.60,0.60,0.50,1.0 }, 32.0);
}

void Ruedas_int_dcha::setMaterial(){
   ruedas_int_dcha1->setMaterial(yellow_plastic);
   ruedas_int_dcha2->setMaterial(yellow_plastic);
   ruedas_int_dcha3->setMaterial(yellow_plastic);
   ruedas_int_dcha4->setMaterial(yellow_plastic);
   ruedas_int_dcha5->setMaterial(yellow_plastic);
   ruedas_int_dcha6->setMaterial(yellow_plastic);
   ruedas_int_dcha7->setMaterial(yellow_plastic);
   ruedas_int_dcha8->setMaterial(yellow_plastic);
   ruedas_int_dcha9->setMaterial(yellow_plastic);
}

void Ruedas_int_dcha::draw(unsigned int modo, bool modoLuz, unsigned int color,  bool ajedrez, bool tapaSup, bool tapaInf){
    glPushMatrix();
      glTranslatef(0.0,-33.0,15.0);
      glScalef(0.5, 0.45, 0.5);
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      ruedas_int_dcha1->draw(0, modoLuz, 0, ajedrez, tapaSup, tapaInf);
   glPopMatrix();

   glPushMatrix();
      glTranslatef(15.0,-33.0,15.0);
      glScalef(0.5, 0.45, 0.5);
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      ruedas_int_dcha2->draw(0, modoLuz, 0, ajedrez, tapaSup, tapaInf);
   glPopMatrix();

   glPushMatrix();
      glTranslatef(-15.0,-33.0,15.0);
      glScalef(0.5, 0.45, 0.5);
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      ruedas_int_dcha3->draw(0, modoLuz, 0, ajedrez, tapaSup, tapaInf);
   glPopMatrix();

   glPushMatrix();
      glTranslatef(-30.0,-33.0,15.0);
      glScalef(0.5, 0.45, 0.5);
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      ruedas_int_dcha4->draw(0, modoLuz, 0, ajedrez, tapaSup, tapaInf);
   glPopMatrix();

   glPushMatrix();
      glTranslatef(30.0,-33.0,15.0);
      glScalef(0.5, 0.45, 0.5);
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      ruedas_int_dcha5->draw(0, modoLuz, 0, ajedrez, tapaSup, tapaInf);
   glPopMatrix();

   glPushMatrix();
      glTranslatef(45.0,-33.0,15.0);
      glScalef(0.5, 0.38, 0.5);
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      ruedas_int_dcha6->draw(0, modoLuz, 0, ajedrez, tapaSup, tapaInf);
   glPopMatrix();
   
   glPushMatrix();
      glTranslatef(-45.0,-33.0,15.0);
      glScalef(0.5, 0.38, 0.5);
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      ruedas_int_dcha7->draw(0, modoLuz, 0, ajedrez, tapaSup, tapaInf);
   glPopMatrix();
   
   glPushMatrix();
      glTranslatef(60.0,-33.0,15.0);
      glScalef(0.4, 0.25, 0.5);
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      ruedas_int_dcha8->draw(0, modoLuz, 0, ajedrez, tapaSup, tapaInf);
   glPopMatrix();
   
   glPushMatrix();
      glTranslatef(-60.0,-33.0,15.0);
      glScalef(0.4, 0.25, 0.5);
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      ruedas_int_dcha9->draw(0, modoLuz, 0, ajedrez, tapaSup, tapaInf);
   glPopMatrix();
}
