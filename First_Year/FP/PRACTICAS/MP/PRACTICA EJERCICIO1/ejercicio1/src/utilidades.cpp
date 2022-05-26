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

bool ordenadoyunico(const double array[], int util){
    bool correcto=true;
    for (int i=0; i<util-1 && correcto;i++){
        if (array[i+1]<=array[i])
            correcto=false;
    }
    
    return correcto;
}


void  mezclarUnico(const double array1[], int utilArray1, const double array2[], int utilArray2, double arraySalida[], int &util_salida){
   
   if(ordenadoyunico(array1,utilArray1) && ordenadoyunico(array2,utilArray2)){    
      int i = 0, j = 0;   
      util_salida=0;
      
        while(i < utilArray1 && j < utilArray2){
    
            if(array1[i] == array2[j]){
                arraySalida[util_salida] = array1[i];
                util_salida++;
                i++;
                j++;
            }
            else if(array1[i] < array2[j]){
                arraySalida[util_salida] = array1[i];
                util_salida++;
                i++;
            }
            else{
            arraySalida[util_salida] = array2[j];
            util_salida++;
            j++;
            }
        }

    if(i < utilArray1){
    for(int k = i; k < utilArray1; k++){
      arraySalida[util_salida] = array1[k];
      util_salida++;
        }
    }
    else if(j < utilArray2){
    for(int k = j; k < utilArray2; k++){
      arraySalida[util_salida] = array2[k];
      util_salida++;
        }
    }
    
   }
   else
       cout << "EL/LOS VECTOR/ES NO ESTÁN ORDENADOS O CONTIENEN ELEMENTOS REPETIDOS" << endl;
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
        bool encontrado=false;
    	for(int j = 0; j < utilArray1 && !encontrado; j++){
	  if(i!=j){
    		if(array1[i] == array1[j]){
                    encontrado=true;
		}
	  }
	}
        if (encontrado){
        for(int k = i; k < utilArray1; k++)
    			{
    				array1[k] = array1[k+1];
			}
    			utilArray1--;
                        i--;
        }             
     }
}
void concatenar(const double array1[], int utilArray1, const  double array2[], int utilArray2, double arraySalida[], int &util_salida){
    util_salida = utilArray1 + utilArray2;
    
    for(int i = 0; i < utilArray1; i++){
    	arraySalida[i] = array1[i];
	}
	
	for(int i = 0; i < utilArray2; i++){
		arraySalida[utilArray1 + i] = array2[i];
	}
}



