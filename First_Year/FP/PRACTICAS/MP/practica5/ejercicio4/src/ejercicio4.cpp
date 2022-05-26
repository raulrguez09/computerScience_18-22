/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   ejercicio1.cpp
 * Author: acid
 *
 * Created on 15 de febrero de 2019, 11:01
 */

#include <iostream>
#include "utilidades.h"
using namespace std;

/*
 * 
 */
int main()
{
    char cadena[] = "Hola, primera cadena de ejemplo";
    char subcadena1[] = "no coincide";
    char subcadena2[] = "Hol";
    char subcadena3[] = "plo";
    char subcadena4[] = "cad";
    
    if (localizarSubcadena(cadena,subcadena1)!=-1){
        cout << subcadena1 << " -- es subcadena de -- " << cadena << endl;
        cout << "POSICION: " << localizarSubcadena(cadena,subcadena1) << endl;
    }
    
    else {
        cout << subcadena1 << " -- no es subcadena de -- " << cadena << endl;
    }

}

