#include "material.h"
using namespace std;

// *****************************************************************************
//
// Clase Material
//
// *****************************************************************************

Material::Material() {
   ambiente  = {0.2, 0.2, 0.2, 1.0};
   difuso    = {0.8, 0.8, 0.8, 1.0};
   especular = {0.0, 0.0, 0.0, 1.0};
   brillo    = 0;
}

Material::Material(Tupla4f mAmbiente, Tupla4f mDifuso, Tupla4f mEspecular, float mBrillo) {
   ambiente = mAmbiente;
   difuso = mDifuso;
   especular = mEspecular;
   brillo = mBrillo;
}

void Material::aplicar() {
   glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambiente);
   glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, difuso);
   glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, especular);
   glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, brillo);
}

void Material::setMaterial(const Material & m){
   ambiente = m.ambiente;
   difuso = m.difuso;
   especular = m.especular;
   brillo = m.brillo;
}