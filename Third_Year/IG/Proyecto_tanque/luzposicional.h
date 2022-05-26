// *****************************************************************************
//
// Clase luzposicional 
//
// *****************************************************************************

#ifndef LUZPOSICIONAL_H_INCLUDED
#define LUZPOSICIONAL_H_INCLUDED

#include "aux.h"
#include "luz.h"

class LuzPosicional : public Luz {
   private:
        float alpha = 0.0;
   public:
        LuzPosicional(Tupla3f posicion, GLenum idLuzOpenGL, Tupla4f ambiente, Tupla4f especular, Tupla4f difuso);
        void animarLuz();
} ;

#endif