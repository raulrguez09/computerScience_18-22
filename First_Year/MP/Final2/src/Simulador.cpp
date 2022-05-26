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
#include "simulador.h"
#include <stdlib.h>
#include <cstdio>
#include <time.h>
#include <cmath>
#include <string>
#include <fstream>
#include <queue>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xatom.h>
#include <X11/keysym.h>

using namespace miniwin;

    Simulador::Simulador(std::string fichero){
        std::string cabecera;
        int capacidad;
        std::ifstream fin;
   
        fin.open(fichero);
        if(fin){
                fin >> cabecera;
                if (cabecera=="MP-PELOTAS-T-1.0"){
                    fin >> ancho;
                    fin >> alto;
                    fin >> capacidad;
            
                    for(int i=0; i<capacidad; i++){
                        Pelota P;
                        fin >> P;
                        original+=P;
               
                    }
                        
                    actual=original;
                }
                else{
                    std::cerr << "error de lectura del fichero (CABECERA INCORRECTA) \n";
                }
        
                if(!fin)
                    std::cerr << "error de lectura del fichero\n";
                fin.close();
                }
        else
            std::cerr << "error de apertura del fichero \n";
   
        if (ancho>=MIN_X && alto >= MIN_Y && ancho<=MAX_X && alto <= MAX_Y)
            vredimensiona(ancho, alto);
        else{
            std::cerr << "error de apertura de ventana (VALORES NO PERMITIDOS)";
            vcierra();
        }
    }
    
    Simulador::~Simulador(){
       vcierra();
       original.~Pelotas();
       actual.~Pelotas();
       
    } 
    
    void Simulador::step (int n){
        for(int i=0; i<n; i++){
            actual.mover();
            actual.colisionarJuego();
        }
        
    }
    
    bool Simulador::salvar(std::string fichero){
        std::ofstream fout;
        bool ok=true;
   
        fout.open(fichero);
        if(fout){
                fout << "MP-PELOTAS-T-1.0" << std::endl;
                fout << ancho << std::endl;
                fout << alto << std::endl;
                fout << actual.getUtil() << std::endl;
                fout << actual;
       
        
                if(!fout){
                    std::cerr << "error de escritura del fichero\n";
                    ok=false;
                }
                fout.close();
        }
        else{
            std::cerr << "error de apertura del fichero \n";
            ok=false;
        }
   
        return ok;
        
    }
    
    const  Pelotas& Simulador::getActual() const{
        return actual;
    }
    
    const  Pelotas& Simulador::getOriginal() const{
        return original;
    }
    
    Pelotas & Simulador::getActual(){
        return actual;
    }
    
