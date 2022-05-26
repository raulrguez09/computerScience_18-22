/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include "miniwin.h"
#include "definiciones.h"
#include "utilidades.h"
#include <stdlib.h>
#include <cstdio>
#include <time.h>
#include <cmath>
#include <string>
#include <queue>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xatom.h>
#include <X11/keysym.h>
using namespace miniwin;


void pinta_pelota(const Bola& P) {
   color((int) P.c);
   circulo_lleno(P.x, P.y, RADIO);
}

void mueve_pelota(Bola& P) {
   const float factor = 0.97;
   P.x += P.dx;
   P.y += P.dy;
   if (P.x > vancho() - RADIO) {
      P.dx = -P.dx * factor;
      P.x = vancho() - RADIO;
   } 
	else if (P.x < RADIO) {
      P.dx = -P.dx * factor;
      P.x = RADIO;
   } 
	else if (P.y > valto() - RADIO) {
      P.dy = -P.dy * factor;
      P.y = valto() - RADIO;
   } 
	else if (P.y < RADIO) {
      P.dy = -P.dy * factor;
      P.y = RADIO;
   }
  // P.dy += 0.1;
}

   Pelota::Pelota(){ //CONSTRUCTOR POR DEFECTO SIN PARAMETROS
        srand(time(NULL));
        x = rand() % MIN_X +1 ;
        y = rand() % MIN_Y +1 ;
        dx = 1 + rand() % MAX_VEL ;
        dy = 1 + rand() % MAX_VEL ;
        color = PColor(rand() % 8);
        /**
        do {
            if(MIN_X<MIN_Y)
                radio= rand() % MIN_X;
            else
                radio= rand() % MIN_Y;
        }while (radio>(MIN_X-x) || radio>(MIN_Y-y));
         **/
    }
    
   Pelota:: Pelota(float X, float Y){ //CONSTRUCTOR CON X,Y
        x = X;
        y = Y;
        dx = 1.0;
        dy = 1.0;
        color = PColor::ROJO;
        
        //RADIO??
        
    }
    
   Pelota:: Pelota(float X, float Y, float DX, float DY, PColor COLOR){
        x=X;
        y=Y;
        dx=DX;
        dy=DY;
        color=COLOR;
        //radio=RADIO;
    }
   
      Pelota:: Pelota(float X, float Y, float DX, float DY, float Radio, PColor COLOR){
        x=X;
        y=Y;
        dx=DX;
        dy=DY;
        color=COLOR;
        radio=Radio;
    }
    
    void Pelota::setPelota(float X, float Y, float DX, float DY, PColor COLOR){
        x=X;
        y=Y;
        dx=DX;
        dy=DY;
        color=COLOR;
        //radio=RADIO;
    }
    
     void Pelota::setPelota(float X, float Y, float DX, float DY,float Radio, PColor COLOR){
        x=X;
        y=Y;
        dx=DX;
        dy=DY;
        color=COLOR;
        radio=Radio;
    }
    
    void Pelota::setPosicion(float X, float Y){
        x=X;
        y=Y;
    }
    
    void Pelota::setDesplazamientos(float DX,float DY){
        dx=DX;
        dy=DY;
    }
    
    void Pelota::setColor(PColor COLOR){
        color=COLOR;
    }
    
    /**void setRadio(float RADIO){
        radio=RADIO;
    }
    */
    
    
    float Pelota::getPosX() const{
        return x;
    }
    
    float Pelota::getPosY() const{
        return y;
    }
    
    float Pelota::getDx() const{
        return dx;
    }
    
    float Pelota::getDy() const{
        return dy;
    }
    
    float Pelota::getRadio() const{
        return radio;
    }
    
    PColor Pelota::getColor() const{
        return color;
    }
    
    void Pelota::mover() {
   const float factor = 0.97;
   x += dx;
   y += dy;
   if (x > MIN_X - getRadio()) {
      dx = -dx * factor;
      x = MIN_X - getRadio();
   } 
	else if (x < getRadio()) {
      dx = -dx * factor;
      x = getRadio();
   } 
	else if (y > MIN_Y - getRadio()) {
      dy = -dy * factor;
      y = MIN_Y - getRadio();
   } 
	else if (y < getRadio()) {
      dy = -dy * factor;
      y = getRadio();
   }
  // P.dy += 0.1;
}
    
   

/**
 * @brief calcula y devuelve la distancia entre la superficie de una pelota con respecto a otra
 * @param otra
 * @return distancia entre las pelotas
 */
double distancia(Pelota p1, Pelota p2){
        float dist = fabs(sqrt(((p2.getPosX() - p1.getPosX())*(p2.getPosX() -p1.getPosX())) + ((p2.getPosY() - p1.getPosY())*(p2.getPosY() - p1.getPosY()))) - p1.getRadio() - p2.getRadio());
        if (dist<=(p1.getRadio() + p2.getRadio()))
            dist=0;
        return dist;
}

/**
 * @brief devuelve bool que dice si dos pelotas colisionan según un UMBRAL
 * @param p1
 * @param p2
 * @return 
 */
bool colisionado(Pelota p1, Pelota p2){
    
    return (distancia(p1,p2)<=UMBRAL);
    
}
/**
 * @brief pinta en pantalla una pelota con sus atributos
 * @param p
 */
void pintar(Pelota &p) {
  color((int) p.getColor());
  circulo_lleno(p.getPosX(), p.getPosY(), p.getRadio());
}

/**
 * @brief Hace colisionar dos pelotas, intercambiando sus desplazamientos
 * @param p1
 * @param p2
 */
void colisionar(Pelota &p1, Pelota &p2){
    if (colisionado(p1,p2)){
        float dx=p1.getDx(), dy=p1.getDy();
        p1.setDesplazamientos(p2.getDx(),p2.getDy());
        p2.setDesplazamientos(dx,dy);
    }
}






    Pelotas::Pelotas(){
        capacidad=1;
        v = new Pelota[capacidad];
        util=0;
    }
    
    Pelotas::Pelotas(int npelotas){
        capacidad = npelotas;
        v = new Pelota[capacidad];
        util = 0;
    }
   
    
    Pelotas::~Pelotas(){
        delete [] v;
    }
    
    int Pelotas::getCapacidad() const{
        return capacidad;
    }
    
    int Pelotas::getUtil() const{
        return util;
    }
    
    void Pelotas::borrar(int pos){
        
        
        Pelota *vnuevo = new Pelota[getCapacidad()];
        
        for(int i=0,j=0; i<getCapacidad();j++){
            if(j!=pos){
             vnuevo[i] = v[j];
             i++;
            }
        }
        
        delete [] v;
        
        v=vnuevo;
        
        util--;
        
        
    }
    
    void Pelotas::aniadir(Pelota p){
        
        if (getUtil()>=getCapacidad())
        {
            Pelota *v_ampliado = new Pelota[getCapacidad()+1];
            
            for(int i=0; i<getCapacidad();i++)
                v_ampliado[i] = v[i];
            
            delete [] v;
            
            v = v_ampliado;
            
            capacidad++;
        }
        
        v[getUtil()]=p;
        util++;
           
    }
    
    Pelota& Pelotas::obtener(int pos){
        return v[pos];
    }
    
    void Pelotas::mover(){
        for(int i=0; i<getUtil();i++)
            v[i].mover();
        
    }
    
    void Pelotas::pintarPelotas(){
        for(int i=0; i<getUtil();i++)
            pintar(v[i]);
    }

    
    void Pelotas::colisionarPelotas(){
               for(int i=0; i<getUtil()-1;i++)
                for(int j=i+1; j<getUtil();j++)
                    colisionar(v[i],v[j]);

    }
    
    void colisionarPelotas(Pelotas &P1, Pelotas &P2){
            for(int i=0; i<P1.getUtil();i++)
                for(int j=0; j<P2.getUtil();j++)
                    colisionar(P1.obtener(i),P2.obtener(j));
    }