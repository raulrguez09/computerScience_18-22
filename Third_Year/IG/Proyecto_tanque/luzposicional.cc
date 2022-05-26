#include "luzposicional.h"

LuzPosicional::LuzPosicional(Tupla3f posicion, GLenum idLuzOpenGL, Tupla4f ambiente, Tupla4f especular, Tupla4f difuso){
    this->posicion = {posicion(0), posicion(1), posicion(2), 1.0};
    id = idLuzOpenGL;
    colorAmbiente = ambiente;
    colorEspecular = especular;
    colorDifuso = difuso;
    activa = false;
};

void LuzPosicional::animarLuz(){
    posicion(0) = 100*cos(alpha) - 100 * sin(alpha);
    posicion(1) = posicion(1);
    posicion(2) = 100*sin(alpha) + 100 * cos(alpha);

    posicion = {posicion(0), posicion(1), posicion(2), 1.0};
    alpha += 0.01;
}


