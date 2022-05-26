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
    
    Pelotas::Pelotas(const Pelotas &original){
        capacidad=original.getCapacidad();
        v = new Pelota [capacidad];
        util = original.getUtil();
        
        for (int i=0; i<util; i++)
            v[i]=original[i];
        
    }
    
    void Pelotas::operator=(const Pelotas &original){
        capacidad=original.getCapacidad();
        delete [] v;
        v = new Pelota [capacidad];
        for(int i=0; i<original.getUtil();i++)
            aniadir(original[i]);
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
    
    Pelota& Pelotas::get(int pos) const{
        return v[pos];
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
    
    void Pelotas::aniadir(const Pelota &p){
        
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
    
    void Pelotas::operator+=(const Pelota &p){
        aniadir(p);
    }
    
    Pelota& Pelotas::obtener(int pos){
        return v[pos];
    }
    
    void Pelotas::mover(){
        for(int i=0; i<getUtil();i++)
            v[i].mover();
        
    }
    
    
    void Pelotas::colisionarPelotas(){
               for(int i=0; i<getUtil()-1;i++)
                for(int j=i+1; j<getUtil();j++)
                    colisionar(v[i],v[j]);

    }
    
    
    
    void Pelotas::colisionarJuego(){
            for(int i=0; i<getUtil()-1;i++)
                for(int j=i+1; j<getUtil();j++)
                {
                    if (colisionado(v[i],v[j])){
                        if(v[i]==v[j]){
                            colisionar(v[i],v[j]);
                            if(v[i].getColor()==PColor::VERDE){
                                Pelota Verde;
                                bool colisiona=true;
                                while(colisiona){
                                    colisiona=false;
                                for(int i=0; i<getUtil() && !colisiona ;i++){
                                    if(colisionado(Verde,get(i)))
                                        colisiona=true;
                                }
                                    if(colisiona){
                                        Pelota p;
                                        Verde=p;
                                    }
                                }
                                aniadir(Verde);
                            }
                        }
                        
                        else{
                            if(v[i].getColor()==PColor::VERDE)
                                borrar(i);
                            else
                                borrar(j);
                        }
                        
                    }
                }

    }
    
    std::ostream& operator<<(std::ostream& os, const Pelotas& p) {
        
        for (int i=0; i<p.getUtil();i++)
            os << p.get(i);
            return os;
        }

    std::istream & operator>>(std::istream & is, Pelotas & p){
        Pelota pl;
        for (int i=0; i<p.capacidad;i++){
            is >> pl;
            p.aniadir(pl);
        }
        return is;
    }


    Pelota& Pelotas::operator[] (int i){
        obtener(i);
    }

     
    Pelota& Pelotas::operator[] (int i) const{
        get(i);
    }



  