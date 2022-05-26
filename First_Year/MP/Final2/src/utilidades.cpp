/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include "miniwin.h"
#include "definiciones.h"
#include "utilidades.h"
#include "pelota.h"
#include "pelotas.h"
#include <cmath>
#include <string.h>

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
      
    }

  

    double distancia(const Pelota &p1, const Pelota &p2){
            float dist = fabs(sqrt(((p2.getPosX() - p1.getPosX())*(p2.getPosX() -p1.getPosX())) + ((p2.getPosY() - p1.getPosY())*(p2.getPosY() - p1.getPosY())))); //distancia entre centros
            if (dist<=(p1.getRadio() + p2.getRadio()))
                dist=0;
            else
                dist=fabs(dist - p1.getRadio() - p2.getRadio());
            return dist;
    }


    bool colisionado(const Pelota &p1, const Pelota &p2){
    
        return (distancia(p1,p2)<=UMBRAL);
    
    }

    void pintar(Pelota &p) {
      color((int) p.getColor());
      circulo_lleno(p.getPosX(), p.getPosY(), p.getRadio());
    }


    void colisionar(Pelota &p1, Pelota &p2){
        if (colisionado(p1,p2)){
            float dx=p1.getDx(), dy=p1.getDy();
            p1.setDesplazamientos(p2.getDx(),p2.getDy());
            p2.setDesplazamientos(dx,dy);
        }
    }
   
    

    void pintar(Pelotas &P){
        for(int i=0; i<P.getUtil();i++)
            pintar(P.obtener(i));
    }
        
    void colisionarPelotas(Pelotas &P1, Pelotas &P2){
            for(int i=0; i<P1.getUtil();i++)
                for(int j=0; j<P2.getUtil();j++)
                    colisionar(P1.obtener(i),P2.obtener(j));
    }
    
   PColor strPColor(std::string c){
        
        PColor color;
        
        if(c=="ROJO")
            color=PColor::ROJO;
        else if(c=="VERDE")
            color=PColor::VERDE;
        else if (c=="AZUL")
            color = PColor::AZUL;
        else if (c=="CYAN")
            color = PColor::CYAN;
        else if (c=="NEGRO")
            color = PColor::NEGRO;
        else if (c=="AMARILLO")
            color = PColor::AMARILLO;
        else if (c=="MAGENTA")
            color = PColor::MAGENTA;
        else if (c=="BLANCO")
            color = PColor::BLANCO;
        
        return color;

    }
    
   
    std::string pcolorStr(PColor c){
        
        std::string color;
        
        if(c==PColor::ROJO)
            color="ROJO";
        else if(c==PColor::VERDE)
            color="VERDE";
        else if (c==PColor::AZUL)
            color = "AZUL";
        else if (c==PColor::CYAN)
            color = "CYAN";
        else if (c==PColor::NEGRO)
            color = "NEGRO";
        else if (c==PColor::AMARILLO)
            color = "AMARILLO";
        else if (c==PColor::MAGENTA)
            color = "MAGENTA";
        else if (c==PColor::BLANCO)
            color = "BLANCO";
        
        return color;

    }
    
    void pintar(Simulador &partida, int tiempo){
      borra();
      pintar(partida.getActual());
      refresca();
      espera(tiempo);
          
    }
   