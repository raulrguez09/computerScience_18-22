#include<iostream>
#include "Functions.hpp"

using namespace std;

//*************************************************************************
//** Lee un valor por teclado que ha de ser entero positivo y lo devuelve
//**

int readNumElem(void)
{
    int n;

    do
    {
        cout << "Número de elementos a insertar: ";
        cin>>n;

        if (n<=0)
           cout << "Debe introducir un valor entero positivo: " <<endl;

        if (n>MAX)
           cout << "...La cantidad maxima permitida es "<< MAX << " : " <<endl;
    } while(n<=0 || n>MAX);

    return n;
}

//*************************************************************************
//*** Selecciona elementos del array V para realizar la operación e imprime
//*** el resultado por pantalla

void choiceElemExpr (int n, double V[])
{
    int i,j,k;
    double resul;

    cout <<endl;

    do
    {
       cout << "Seleccione posicion V[i]: "; cin >>i;
    } while (i>=n || i<0);

    do
    {
       cout << "Seleccione posicion V[j]: ";cin >>j;
    } while (j>=n || j<0);

    do
    {
       cout << "Seleccione posicion V[k]: ";cin >>k;
    } while (k>=n || k<0);
 
    resul= (V[i]+V[j])*V[k];
    cout << "(V[" << i <<"] + V[" << j << "]) * V[" << k << "] = " << resul <<endl;
 
}

//*************************************************************************

