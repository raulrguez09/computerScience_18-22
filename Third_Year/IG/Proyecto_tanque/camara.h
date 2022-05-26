// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: camara.h
//
// #############################################################################

#ifndef CAMARA_H_INCLUDED
#define CAMARA_H_INCLUDED

#include "aux.h"

typedef enum {NO_SELECCION, BALA, LATA} tipoSeleccion;

// *****************************************************************************
//
// Clase CAMARA (práctica 6)
//
// *****************************************************************************
class Camara{
    public:
    Camara();
    Camara(Tupla3f eye, Tupla3f at, Tupla3f up, int tipo, float left, float right, float top, float bottom, float near, float far);

    void girar_Examinar(float angX, float angY);
    void girar(float angX, float angY);
    
    void rotarXExaminar(float angle);
    void rotarYExaminar(float angle);
    void rotarZExaminar(float angle);

    void rotarXFirstPerson(float angle);
    void rotarYFirstPerson(float angle);
    void rotarZFirstPerson(float angle);

    void mover(float eje_x, float eje_y, float eje_z);
    void zoom(float factor);

    void setAt(Tupla3f at);
    void setObserver();
    void setProyeccion();
    
    void setSeleccion(tipoSeleccion tipo){
        objetoSeleccionado=tipo;
    }
    
    void setLeft(float n){
        left = n;
    }

    void setRight(float n){
        right = n;
    }

    float getTop(){
        return top;
    }

    float getBottom(){
        return bottom;
    }

    void reestablecerEye(){
        eye = eye_original;
    }

    tipoSeleccion getObjetoSeleccionado(){
        return objetoSeleccionado;
    };

    protected:
        Tupla3f eye;
        Tupla3f eye_original;
        Tupla3f at;
        Tupla3f up;
        tipoSeleccion objetoSeleccionado = NO_SELECCION;

        int tipo; // 0 -> ORTOGONAL, 1 -> PERSPECTIVA
        float left, right, near, far, top, bottom;
};

#endif

