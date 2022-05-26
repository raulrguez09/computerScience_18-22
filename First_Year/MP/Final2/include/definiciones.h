/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   definiciones.h
 * Author: cristian
 *
 * Created on 7 de mayo de 2019, 22:52
 */

//Alumno 1: Fernández Jiménez, Cristian
//Alumno 2: Crespo Arco, Cristina María

#ifndef DEFINICIONES_H
#define DEFINICIONES_H

#include "miniwin.h"
using namespace miniwin;

/* "Color" es un tipo enumerado definido en Miniwin.h. 
Una variable de tipo Color puede tomar los siguientes valores:
NEGRO, ROJO, VERDE, AZUL, AMARILLO, MAGENTA, CYAN, BLANCO
No queremos que el diseño del los objetos dependan del interfaz gráfico por lo que se define 
PColor un enumerado propio que coincide... por "pura coincidencia"!
*/
enum class PColor {
  NEGRO, ROJO, VERDE, AZUL,
  AMARILLO, MAGENTA, CYAN, BLANCO
};

/*
 @brief Constantes para trabajar con la clase Pelota y Simulador
 */
const int UMBRAL=0;
const int MIN_X=400;
const int MIN_Y=400;
const int MAX_X=800;
const int MAX_Y=600;
const int MAX_VEL=10;
const int RADIO = 20;

#endif /* DEFINICIONES_H */

