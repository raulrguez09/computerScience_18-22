#include<iostream>
#include "ArrayProc.hpp"

using namespace std;

//**************************************************
//** Lee valores desde teclado y lo inserta
//** en un vector.

void readVectorElements (int cant, double n[])
{
    int i;
    for(i=0;i<cant;i++)
    {
        cout<<"Ingresa elemento en V["<<i<<"] : ";
        cin>>n[i];
    }
 
}
 
//**************************************************
//** Muestra los valores de un vector
//** por pantalla

void showVectorElements (int cant, double n[])
{
    int i;
    for(i=0;i<cant;i++)
    {
        cout<<"V["<<i<<"] : "<<n[i]<<endl;
    }
}

//**************************************************

