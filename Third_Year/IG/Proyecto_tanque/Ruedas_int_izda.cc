#include "Ruedas_int_izda.h"

// *****************************************************************************
//
// Clase Ruedas_int_izda.cc
//
// *****************************************************************************

Ruedas_int_izda::Ruedas_int_izda(){
    ruedas_int_izda1 = new Cilindro(9, 50, 20, 5, 'z', 0);
    ruedas_int_izda2 = new Cilindro(9, 50, 20, 5, 'z', 0);
    ruedas_int_izda3 = new Cilindro(9, 50, 20, 5, 'z', 0);
    ruedas_int_izda4 = new Cilindro(9, 50, 20, 5, 'z', 0);
    ruedas_int_izda5 = new Cilindro(9, 50, 20, 5, 'z', 0);
    ruedas_int_izda6 = new Cilindro(9, 50, 20, 5, 'z', 0);
    ruedas_int_izda7 = new Cilindro(9, 50, 20, 5, 'z', 0);
    ruedas_int_izda8 = new Cilindro(9, 50, 20, 5, 'z', 0);
    ruedas_int_izda9 = new Cilindro(9, 50, 20, 5, 'z', 0);
    yellow_plastic = Material({0.0,0.0,0.0,1.0 }, {0.5,0.5,0.0,1.0 }, {0.60,0.60,0.50,1.0 }, 32.0);
}

void Ruedas_int_izda::setMaterial(){
   ruedas_int_izda1->setMaterial(yellow_plastic);
   ruedas_int_izda2->setMaterial(yellow_plastic);
   ruedas_int_izda3->setMaterial(yellow_plastic);
   ruedas_int_izda4->setMaterial(yellow_plastic);
   ruedas_int_izda5->setMaterial(yellow_plastic);
   ruedas_int_izda6->setMaterial(yellow_plastic);
   ruedas_int_izda7->setMaterial(yellow_plastic);
   ruedas_int_izda8->setMaterial(yellow_plastic);
   ruedas_int_izda9->setMaterial(yellow_plastic);
}

void Ruedas_int_izda::draw(unsigned int modo, bool modoLuz, unsigned int color,  bool ajedrez, bool tapaSup, bool tapaInf){
    glPushMatrix();
      glTranslatef(0.0,-33.0,-45.0);
      glScalef(0.5, 0.45, 0.5);
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      ruedas_int_izda1->draw(0, modoLuz, 0, ajedrez, tapaSup, tapaInf);
   glPopMatrix();

   glPushMatrix();
      glTranslatef(15.0,-33.0,-45.0);
      glScalef(0.5, 0.45, 0.5);
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      ruedas_int_izda2->draw(0, modoLuz, 0, ajedrez, tapaSup, tapaInf);
   glPopMatrix();

   glPushMatrix();
      glTranslatef(-15.0,-33.0,-45.0);
      glScalef(0.5, 0.45, 0.5);
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      ruedas_int_izda3->draw(0, modoLuz, 0, ajedrez, tapaSup, tapaInf);
   glPopMatrix();

   glPushMatrix();
      glTranslatef(-30.0,-33.0,-45.0);
      glScalef(0.5, 0.45, 0.5);
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      ruedas_int_izda4->draw(0, modoLuz, 0, ajedrez, tapaSup, tapaInf);
   glPopMatrix();

   glPushMatrix();
      glTranslatef(30.0,-33.0,-45.0);
      glScalef(0.5, 0.45, 0.5);
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      ruedas_int_izda5->draw(0, modoLuz, 0, ajedrez, tapaSup, tapaInf);
   glPopMatrix();

   glPushMatrix();
      glTranslatef(45.0,-33.0,-45.0);
      glScalef(0.5, 0.38, 0.5);
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      ruedas_int_izda6->draw(0, modoLuz, 0, ajedrez, tapaSup, tapaInf);
   glPopMatrix();
   
   glPushMatrix();
      glTranslatef(-45.0,-33.0,-45.0);
      glScalef(0.5, 0.38, 0.5);
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      ruedas_int_izda7->draw(0, modoLuz, 0, ajedrez, tapaSup, tapaInf);
   glPopMatrix();
   
   glPushMatrix();
      glTranslatef(60.0,-33.0,-45.0);
      glScalef(0.4, 0.25, 0.5);
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      ruedas_int_izda8->draw(0, modoLuz, 0, ajedrez, tapaSup, tapaInf);
   glPopMatrix();
   
   glPushMatrix();
      glTranslatef(-60.0,-33.0,-45.0);
      glScalef(0.4, 0.25, 0.5);
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      ruedas_int_izda9->draw(0, modoLuz, 0, ajedrez, tapaSup, tapaInf);
   glPopMatrix();
}
