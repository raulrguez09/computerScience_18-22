/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: crisfj00
 *
 * Created on 2 de abril de 2019, 12:07
 */

#include <cstdlib>
#include<iostream>
#include<string.h>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    
    if(argc==5){
        
        if(strcmp(argv[1],"-c")==0 && strcmp(argv[3],"-s")==0){
            if (localizarSubcadena(argv[2],argv[4])!=0){
                cout << argv[4] << " -- es subcadena de -- " << argv[2] << endl;
                cout << "VECES: " << localizarSubcadena(argv[2],argv[4]) << endl;
            }
    
            else {
                cout << argv[4] << " -- no es subcadena de -- " << argv[2] << endl;
            }
        }
        
        else if(strcmp(argv[1],"-s")==0 && strcmp(argv[3],"-c")==0){
            if (localizarSubcadena(argv[4],argv[2])!=0){
                cout << argv[2] << " -- es subcadena de -- " << argv[4] << endl;
                cout << "VECES: " << localizarSubcadena(argv[4],argv[2]) << endl;
            }
    
            else {
                cout << argv[2] << " -- no es subcadena de -- " << argv[4] << endl;
            }
        }
        
        else 
            cout << "LOS ARGUMENTOS HAN SIDO MAL INTRODUCIDOS" << endl << "AYUDA: ejercicio -s/-c subcadena/cadena -c/-s cadena/subcadena (4 ARGUMENTOS)" << endl;
        
    }
    
    else
        cout << "EL NÚMERO DE ARGUMENTOS NO ES EL CORRECTO" << endl << "AYUDA: ejercicio -s/-c subcadena/cadena -c/-s cadena/subcadena (4 ARGUMENTOS)" << endl;
    
    
    

    return 0;
}

