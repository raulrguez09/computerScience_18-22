/**
 * Fichero de implementacion de las funciones que se piden
 */
#include <iostream> 
#include <cstdlib>
#include "utilidades.h"
#include<string.h>
using namespace std;

/**
@brief Escribe la longitud y los elementos de la cadena en la salida estándar
@param cadena La cadena a imprimir
@param util_cadena Número de elementos útiles en la cadena
*/
void imprimirCadena(const char cadena[],int util_cadena){
    cout << util_cadena << " ";
    for(int i=0; i<util_cadena; ++i)
    {
        cout<<cadena[i]<<" ";
    }
    cout<<endl;
}

/**
 * @brief Devuelve la longititud de la cadena introducida
 * @param cadena
 * @return longitud de la cadena
 */
int longitud(const char cadena[]){
    int i=0;
    while (cadena[i]!='\0')
        i++;
    return i;
}

/**
 * @brief Comprueba si la segunda cadena está contenida en la primera.
 * @param cadena
 * @param subcadena
 * @return Posición dónde comienza la subcadena. Si devuelve -1, no se encuentra contenida.
 */
int localizarSubcadena(const char cadena[], const char subcadena[]){
    int contador=0;
    int i=0, j=0;
    bool coincide=false;
    while(i<longitud(cadena) && j<longitud(subcadena)){
        if (cadena[i]!=subcadena[j]){
            i++;
            coincide=false;
        }
        else{
            coincide=true;
            i++;
            j++;
        }
        
        if(!coincide)
            j=0;
        else if (coincide && j==longitud(subcadena)){
                contador++;
                j=0;
            
        }
        
    }
    
    return contador;
    
}



