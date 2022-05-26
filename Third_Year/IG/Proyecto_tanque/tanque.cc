#include "aux.h"
#include "tanque.h"
using namespace std;

// *****************************************************************************
//
// Clase tanque.cc 
//
// *****************************************************************************

Tanque::Tanque(){
    base = new BaseTanque();
    pinchos  = new Pinchos();
    rueda_ext = new Rueda_ext();
    ruedas_int_izda = new Ruedas_int_izda();
    ruedas_int_dcha = new Ruedas_int_dcha();
    casco = new Casco();
    canon = new Canon();
}

void Tanque::draw(unsigned int modo, bool modoLuz, unsigned int color,  bool ajedrez, bool tapaSup, bool tapaInf){

  //Casco Superior
  glPushMatrix();
    glRotatef(giroCasco, 0.0, 1.0, 0.0);
    glRotatef(elevCanon, 0.0, 0.0, 1.0);
    //Canon
    glPushMatrix();
      glTranslatef(traslCanon + 30.0,45.0,0.0);
      glScalef(1.0, 0.5, 0.5);
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      canon->draw(modo, modoLuz, 0, ajedrez, tapaSup, tapaInf);
    glPopMatrix();

    //Casco
    glPushMatrix();
      glTranslatef(0.0,30.0,0.0);
      glScalef(2.0, 2.0, 2.0);
      casco->draw(modo, modoLuz, 0, ajedrez, tapaSup, tapaInf);
    glPopMatrix();
  glPopMatrix();

  //Base Inferior Tanque
  glPushMatrix();
    glRotatef(giroBaseInferior, 0.0, 1.0, 0.0);
    //Base tanque
    glPushMatrix();
        glScalef(1.5, 0.5, 1.0);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        base->draw(modo, modoLuz, 0, ajedrez);
    glPopMatrix();
    //Pinchos
    glPushMatrix();
      pinchos->draw(modo, modoLuz, 0, ajedrez);
    glPopMatrix();

    //Ruedas Tanque
    glPushMatrix();
      //Rueda_Ext
      glPushMatrix();
        glTranslatef(0.0,-33.0,-45.0);
        glScalef(4.7, 0.5, 1.5);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        rueda_ext->draw(modo, modoLuz, 0, ajedrez, true, true);
      glPopMatrix();
      
      //Ruedas_int_izda
      glPushMatrix();
        ruedas_int_izda->draw(modo, modoLuz, color, ajedrez, true, true);
      glPopMatrix();

      //Ruedas_int_izda
      glPushMatrix();
        ruedas_int_dcha->draw(modo, modoLuz, color, ajedrez, true, true);
      glPopMatrix();
    glPopMatrix();

  glPopMatrix();
}

void Tanque::modificarGiroCasco(float giro){
    giroCasco += giro;
}

void Tanque::modificarElevCanon(float elev){
  elevCanon += elev;

  if(elevCanon >= 20){
    elevCanon = 20;
  }

  if(elevCanon <= 0){
    elevCanon = 0;
  }
}

void Tanque::modificarTraslCanon(float trasl){
    traslCanon += trasl;
    
    if(traslCanon > 3){
      traslCanon = 3;
    }
    if(traslCanon < -60){
      traslCanon = -60;
    }
}

void Tanque::modificarGiroBaseInferior(float giro){
  giroBaseInferior += giro;
}

void Tanque::seleccionaModifGrados(int grado, char signo){
  if(grado == 0 && signo == '+'){
    cout << "AUMENTANDO GIRCO CASCO" << endl;
    modificarGiroCasco(20);
  }

  if(grado == 1 && signo == '+'){
    cout << "ELEVO EL CANON" << endl;
    modificarElevCanon(5);
  }

  if(grado == 2 && signo == '+'){
    cout << "TRASLADO EL CANON HACIA DENTRO" << endl;
    modificarTraslCanon(10);
  }
            
  if(grado == 3 && signo == '+'){
    cout << "ROTO LA BASE INFERIOR" << endl;
    modificarGiroBaseInferior(20);
  }

  if(grado == 0 && signo == '-'){
    cout << "AUMENTANDO GIRCO CASCO" << endl;
    modificarGiroCasco(-20);
  }

  if(grado == 1 && signo == '-'){
    cout << "ELEVO EL CANON" << endl;
    modificarElevCanon(-5);
  }

  if(grado == 2 && signo == '-'){
    cout << "TRASLADO EL CANON HACIA DENTRO" << endl;
    modificarTraslCanon(-10);
  }
            
  if(grado == 3 && signo == '-'){
    cout << "ROTO LA BASE INFERIOR" << endl;
    modificarGiroBaseInferior(-20);
  }  
}

void Tanque::animacion(){
  if(giroBaseInferior >= 360){
    factorGiros = -factorGiros;
  }
  else if(giroBaseInferior < 0){
    factorGiros = -factorGiros;
  }

  if(elevCanon >= 20){  
    factorElev = -factorElev;
  }
  else if(elevCanon <= 0){
    factorElev = -factorElev;
  }

  if(traslCanon >= 3){
    factorTrasl = -factorTrasl;
  }
  else if(traslCanon <= -60){
    factorTrasl = -factorTrasl;
  }

  modificarElevCanon(-factorElev);
  modificarTraslCanon(factorTrasl);
  modificarGiroBaseInferior(factorGiros);
  modificarGiroCasco(-factorGiros);
}

void Tanque::setMaterial(){
  pinchos->setMaterial();
  casco->setMaterial();
  canon->setMaterial();
  base->setMaterial();
  rueda_ext->setMaterial();
  ruedas_int_izda->setMaterial();
  ruedas_int_dcha->setMaterial();
}