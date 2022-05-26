// *****************************************************************************
//
// Clase luzdireccional 
//
// *****************************************************************************

#ifndef LUZDIRECCIONAL_H_INCLUDED
#define LUZDIRECCIONAL_H_INCLUDED

#include "aux.h"
#include "luz.h"

class LuzDireccional : public Luz {
   protected:
      float alpha;
      float beta;
   public:
        // inicializar la fuente de luz
        LuzDireccional(Tupla2f direccion, GLenum idLuzOpenGL, Tupla4f ambiente, Tupla4f especular, Tupla4f difuso);

        // Cambiar ángulo:
        void variarAnguloAlpha(float incremento);
        void variarAnguloBeta(float incremento);
};

#endif