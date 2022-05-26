// #############################################################################
//
// Archivo: material.h
//
// #############################################################################

#ifndef MATERIAL_H_INCLUDED
#define MATERIAL_H_INCLUDED

#include "aux.h"

class Material {
    protected:
        Tupla4f ambiente;
        Tupla4f difuso;
        Tupla4f especular;
        float brillo;
   
    public:
        Material();
        Material (Tupla4f mAmbiente, Tupla4f mDifuso, Tupla4f mEspecular, float mBrillo);
        void aplicar();
        void setMaterial(const Material & material);
} ;

#endif