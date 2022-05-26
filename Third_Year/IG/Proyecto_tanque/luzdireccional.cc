#include "luzdireccional.h"
#include <math.h>
using namespace std;

// *****************************************************************************
//
// Clase LuzDireccional
//
// *****************************************************************************


LuzDireccional::LuzDireccional(Tupla2f direccion, GLenum idLuzOpenGL, Tupla4f ambiente, Tupla4f especular, Tupla4f difuso){
    id = idLuzOpenGL;
    colorAmbiente = ambiente;
    colorEspecular = especular;
    colorDifuso = difuso;
    
    activa = false;

    alpha = direccion(0)*M_PI/180;
    beta = direccion(1)*M_PI/180;

    this->posicion = {sin(alpha)*cos(beta), sin(alpha)*sin(beta), cos(alpha), 0.0};
}

void LuzDireccional::variarAnguloAlpha(float incremento) {
    alpha += incremento * M_PI/180;
    
    if(alpha > (2*M_PI)){
        alpha -= 2*M_PI;
    }
    if(alpha <-2*M_PI){
        alpha += 2*M_PI;
    }

    this->posicion[0] = sin(alpha)*cos(beta);
    this->posicion[1] = sin(alpha)*sin(beta);
    this->posicion[2] = cos(alpha);
}

void LuzDireccional::variarAnguloBeta(float incremento) {
    beta += incremento * M_PI/180;
    if(beta > 2*M_PI){
        beta -= 2*M_PI;
    }
    if(beta <-2*M_PI){
        beta += 2*M_PI;
    }

    this->posicion[0] = sin(alpha)*cos(beta);
    this->posicion[1] = sin(alpha)*sin(beta);
    this->posicion[2] = cos(alpha);   
}