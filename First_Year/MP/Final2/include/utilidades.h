/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   utilidades.h
 * Author: cristian
 *
 * Created on 7 de mayo de 2019, 22:53
 */

//Alumno 1: Fernández Jiménez, Cristian
//Alumno 2: Crespo Arco, Cristina María


#ifndef UTILIDADES_H
#define UTILIDADES_H

#include "pelota.h"
#include "pelotas.h"
#include "simulador.h"






struct Bola {
   float x, y;
   float dx, dy;
   PColor c;
};

void pinta_pelota(const Bola& P);

void mueve_pelota(Bola& P);



/**
 * @brief calcula y devuelve la distancia entre la superficie de una pelota con respecto a otra
 * @param otra
 * @return distancia entre las pelotas
 */
double distancia(const Pelota &p1, const Pelota &p2);

/**
 * @brief devuelve bool que dice si dos pelotas colisionan según un UMBRAL
 * @param p1
 * @param p2
 * @return 
 */
bool colisionado(const Pelota &p1, const Pelota &p2);
/**
 * @brief pinta en pantalla una pelota con sus atributos
 * @param p
 */
void pintar(Pelota &p);

/**
 * @brief Hace colisionar dos pelotas, intercambiando sus desplazamientos
 * @param p1
 * @param p2
 */
void colisionar(Pelota &p1, Pelota &p2);



/**
 * @brief Pinta en pantalla todas las pelotas del conjunto
 * @param P
 */
void pintar(Pelotas &P);

/**
 * @brief Colisiona las pelotas de un conjunto P1 con las del conjunto P2
 * @param P1
 * @param P2
 */
void colisionarPelotas(Pelotas &P1, Pelotas &P2);

/**
 * @brief Dado un string devuelve el PColor correspondiente
 * @param c
 * @return PColor::c
 */
PColor strPColor(std::string c);

/**
 * @brief Dado un PColor devuelve el string que lo identifica
 * @param c
 * @return string color
 */
std::string pcolorStr(PColor c);

/**
 * @brief Se encarga de realizar las funciones de borrar, pintar, refrescar y esperar sobre el conjunto de Pelotas actual
 * @param partida
 * @param tiempo
 */
void pintar(Simulador &partida, int tiempo);

#endif /* UTILIDADES_H */

