/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "Objetivo.h"
#include "Alquiler.h"
#include "iostream"
using namespace std;

vector<Alquiler> Objetivo::conseguirAlquileres(string deporte){
    vector<Alquiler> alq;
    for(int i = 0; i < alquileres.size(); i++){
        if(alquileres[i].getDeporte() == deporte){
            alq.push_back(alquileres[i]);
        }
    }
    
    return alq;
}

float Objetivo::calcularCosteMedio(vector<Alquiler> alq){
    float coste = 0.0, coste_medio = 0.0;
    for(int i = 0 ; i < alq.size(); i++){
        coste += alq[i].getPrecio();
    }
    coste_medio = coste/alq.size();
    
    return coste_medio;
}

float Objetivo::calcularTiempoMedio(vector<Alquiler> alq){
    float tmp = 0.0, tiempo_medio = 0.0;
    for(int i = 0 ; i < alq.size(); i++){
        tmp += alq[i].getTiempo();
    }
    tiempo_medio = tmp/alq.size();
    
    return tiempo_medio;
}

void Objetivo::nuevoAlquiler(Alquiler alq){
    alquileres.push_back(alq);
}

void Objetivo::mostrarObjetivo(){
    vector<Alquiler> alq;
    vector<string> deporte = {"Futbol", "Baloncesto", "Volleyball"};
    
    cout << "Tiempo y coste medio de los alquileres" << endl;
    cout << "Numero total de alquileres: " << alquileres.size() << endl << endl;
    
    for(int i = 0; i < deporte.size(); i++){
        vector<Alquiler> alq;
        float tmp_medio = 0.0, coste_medio = 0.0;
        alq = conseguirAlquileres(deporte[i]);
        
        if(alq.size() != 0){
            tmp_medio = calcularTiempoMedio(alq);
            coste_medio = calcularCosteMedio(alq); 
        }
        
        cout << "Los resultados para el " << deporte[i] << " son:" << endl;
        cout << "Numero de alquileres: " << alq.size() << endl;
        cout << "Tiempo medio de alquiler: " << tmp_medio << " minutos" << endl;
        cout << "Coste medio de alquiler: " << coste_medio << " euros" << endl << endl;
        
        
    }
}