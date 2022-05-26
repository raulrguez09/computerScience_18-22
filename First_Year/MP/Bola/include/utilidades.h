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

#ifndef UTILIDADES_H
#define UTILIDADES_H


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

struct Bola {
   float x, y;
   float dx, dy;
   PColor c;
};

void pinta_pelota(const Bola& P);

void mueve_pelota(Bola& P);

class Pelota{
private:
  float x,y;
  float dx, dy;
  float radio=RADIO;
  PColor color;
  
public:
   Pelota();
    
    Pelota(float X, float Y);
    
    Pelota(float X, float Y, float DX, float DY, PColor COLOR);
    
    Pelota(float X, float Y, float DX, float DY, float Radio, PColor COLOR);

    void setPelota(float X, float Y, float DX, float DY, PColor COLOR);
    
    void setPelota(float X, float Y, float DX, float DY, float Radio, PColor COLOR);

    void setPosicion(float X, float Y);
    
    void setDesplazamientos(float DX,float DY);
    
    void setColor(PColor COLOR);
    float getPosX() const;
    
    float getPosY() const;
    float getDx() const;
    
    float getDy() const;
    
    float getRadio() const;
    PColor getColor() const; 
    
    void mover() ;
    
   
};

/**
 * @brief calcula y devuelve la distancia entre la superficie de una pelota con respecto a otra
 * @param otra
 * @return distancia entre las pelotas
 */
double distancia(Pelota p1, Pelota p2);

/**
 * @brief devuelve bool que dice si dos pelotas colisionan según un UMBRAL
 * @param p1
 * @param p2
 * @return 
 */
bool colisionado(Pelota p1, Pelota p2);
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


class Pelotas{
private: 
    Pelota *v;
    int capacidad;
    int util;
public:
    
    Pelotas();
    
    Pelotas(int npelotas);
    
    ~Pelotas();
    
    int getCapacidad() const;
    
    int getUtil() const;
    
    void borrar(int pos);
    
    /**
     * @brief Se añade una Pelota al conjunto, al final, realojando si es necesario
     * @param p
     */
    void aniadir(Pelota p);
    
    /**
     * @brief Se obtiene la Pelota de la posición dada y es posible editarla
     * @param pos
     * @return 
     */
    Pelota& obtener(int pos);
    
    void mover();
    
    void pintarPelotas();
    
    /**
     * @brief Colisiona las pelotas de un mismo conjunto
     */
    void colisionarPelotas();
    
};
/**
 * @brief Colisiona las pelotas de un conjunto P1 con las del conjunto P2
 * @param P1
 * @param P2
 */
 void colisionarPelotas(Pelotas &P1, Pelotas &P2);

#endif /* UTILIDADES_H */

