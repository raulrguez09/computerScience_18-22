/**
 * Fichero de implementacion de las funciones que se piden
 */
#include <iostream> 
#include "utilidades.h"
using namespace std;

/**
 * @brief lee el vector y devuelve el numero de componentes en util_array
 * @param array
 * @param util_array
 */
void leer(double array[], int &util_array){
    cout << "Cuantos: ";
    cin >> util_array;
    for(int i=0; i<util_array; ++i)
    {
        cin >> array[i];
    }
    cout<<endl;
}

/**
@brief Escribe la longitud y los elementos del array en la salida estándar
@param array El array a imprimir
@param util_array Número de elementos útiles en el array
@pre array puede no contener ningun elemento
*/
void imprimirArray(const double array[],int util_array){
    cout << util_array << " ";
    for(int i=0; i<util_array; ++i)
    {
        cout<<array[i]<<" ";
    }
    cout<<endl;
}

void  mezclarUnico(const double array1[], int utilArray1, const double array2[], int utilArray2, double arraySalida[], int &util_salida){
	bool ascendente = true;
	ordenar(array1, utilArray1, ascendente);
	ordenar(array2, utilArray2, ascendente);
	
	unico(array1, utilArray1);
	unico(array2, utilArray2);
	
	concatenar(array1, utilArray1, array2, utilArray2, arraySalida, util_salida);
}

void ordenar(double v[], int util_v, bool asc){
	if(asc)
	{
		bool cambio = true;
		int intercambia;
		for (int izda = 0; izda < util_v && cambio; izda++){
			cambio = false;
			for (int i = util_v-1 ; i > izda ; i--){
				if (v[i] < v[i-1]){
					cambio = true;
					intercambia = v[i];
					v[i] = v[i-1];
					v[i-1] = intercambia;
				}
			}
		}
	}
	else
	{
		bool cambio = true;
		int intercambia;
		for (int izda = 0; izda < util_v && cambio; izda++){
			cambio = false;
			for (int i = util_v-1 ; i > izda ; i--){
				if (v[i] > v[i-1]){
					cambio = true;
					intercambia = v[i];
					v[i] = v[i-1];
					v[i-1] = intercambia;
				}
			}
		}
	}
}

void unico (double array1[], int &utilArray1){
    for (int i = 0; i < utilArray1; i++){
    	for(int j = 0; j < utilArray1; j++){
	  if(i!=j){
    		if(array1[i] == array1[j]){
    			for(int k = i; k < utilArray1; k++)
    			{
    				array1[k] = array1[k+1];
			}
    			utilArray1--;
		}
	  }
	}
     }
} /*????????????????????????????????????????*/
void concatenar(const double array1[], int utilArray1, const  double array2[], int utilArray2, double arraySalida[], int &util_salida){
    util_salida = utilArray1 + utilArray2;
    
    for(int i = 0; i < utilArray1; i++){
    	arraySalida[i] = array1[i];
	}
	
	for(int i = 0; i < utilArray2; i++){
		arraySalida[utilArray1 + i] = array2[i];
	}
}


