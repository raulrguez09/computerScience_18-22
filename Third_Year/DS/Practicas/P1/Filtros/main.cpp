/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: raulrguez
 *
 * Created on 4 de abril de 2021, 10:02
 */

#include <cstdlib>
#include <iostream>
#include "GestorFiltros.h"
#include "Cliente.h"
#include "Objetivo.h"
#include <time.h>
using namespace std;

/*
 * 
 */


int main(int argc, char** argv) {
    srand(time(NULL));

    GestorFiltros gestor;
    Objetivo target;
   
    for(int i = 0 ; i < 10 ; i++){
        Cliente client;
        Alquiler a = client.getAlquiler();
        gestor.filtrar(a);
        client.setAlquiler(a);
        target.nuevoAlquiler(client.getAlquiler());
        if(i%5 == 0){
            target.mostrarObjetivo();
        }
    }

}

