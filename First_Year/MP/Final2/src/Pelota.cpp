/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "miniwin.h"
#include "definiciones.h"
#include "utilidades.h"
#include "pelota.h"


 Pelota::Pelota(){ 
        
        x = rand() % MIN_X +1 ;
        y = rand() % MIN_Y +1 ;
        dx = 1 + rand() % MAX_VEL ;
        dy = 1 + rand() % MAX_VEL ;
        color = PColor::VERDE;
       
    }
    
   Pelota:: Pelota(float X, float Y){ 
        x = X;
        y = Y;
        dx = 1.0;
        dy = 1.0;
        color = PColor::ROJO;
        
    }
    
   Pelota:: Pelota(float X, float Y, float DX, float DY, PColor COLOR){
        x=X;
        y=Y;
        dx=DX;
        dy=DY;
        color=COLOR;
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
    
    bool Pelota::operator==(const Pelota &P){
        return (color==P.getColor() && radio==P.getRadio());
    }
    
    void Pelota::operator=(const Pelota &P){
        x = P.getPosX();
        y = P.getPosY();
        dx = P.getDx();
        dy = P.getDy();
        color = P.getColor();
        radio = P.getRadio();
    }
    
    void Pelota::mover() {
        const float factor = 0.97;
        x += dx;
        y += dy;
        if (x > vancho() - getRadio()) {
            dx = -dx * factor;
            x = vancho() - getRadio();
        } 
	else if (x < getRadio()) {
            dx = -dx * factor;
            x = getRadio();
        } 
	else if (y > valto() - getRadio()) {
            dy = -dy * factor;
            y = valto() - getRadio();
        } 
	else if (y < getRadio()) {
            dy = -dy * factor;
            y = getRadio();
        }
  
}
    
    
         std::ostream& operator<<(std::ostream& os, const Pelota& p) {
        
            os << p.getPosX() << " " << p.getPosY() << " " << p.getDx() << " " << p.getDy() << " " << p.getRadio() << " " << pcolorStr(p.getColor()) << "\n";
             
            return os;
        }   
  
        std::istream & operator>>(std::istream & is, Pelota & p){
            std::string c;
            is >> p.x;
            is >> p.y;
            is >> p.dx >> p.dy >> p.radio;
            is >> c;
            p.color=strPColor(c);

            return is;
    
        }