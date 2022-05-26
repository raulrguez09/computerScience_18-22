// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Tanque.h

//
// #############################################################################

#ifndef TANQUE_H_INCLUDED
#define TANQUE_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include "objrevolucion.h"
#include "cubo.h"
#include "BaseTanque.h"
#include "Casco.h"
#include "Pinchos.h"
#include "Canon.h"
#include "Rueda_ext.h"
#include "Ruedas_int_izda.h"
#include "Ruedas_int_dcha.h"

class Tanque {
    private:
        BaseTanque * base = nullptr;
        Pinchos * pinchos  = nullptr;
        Rueda_ext * rueda_ext = nullptr;
        Ruedas_int_izda * ruedas_int_izda = nullptr;
        Ruedas_int_dcha * ruedas_int_dcha = nullptr;
        Casco * casco =  nullptr;
        Canon * canon = nullptr;

        float giroBaseInferior = 0.0;
        float giroCasco = 0.0;
        float elevCanon = 0.0; 
        float traslCanon = 0.0;

        float factorGiros = 1.0;
        float factorElev = 1.0;
        float factorTrasl = 1.0;
        float velocidad = 1.1;

    public:
        Tanque();
        void setMaterial();
        void draw(unsigned int modo, bool modoLuz, unsigned int color,  bool ajedrez, bool tapaSup, bool tapaInf);
        void modificarGiroCasco(float giro);
        void modificarElevCanon(float elev);
        void modificarTraslCanon(float trasl);
        void modificarGiroBaseInferior(float giro);
        void animacion();
        void seleccionaModifGrados(int grado, char signo);
};

#endif