//Alumno1: Fernández Jiménez, Cristian.
//Alumno2: Crespo Arco, Cristina María.

#ifndef UTILIDADES_H
#define UTILIDADES_H

/**
 * @brief lee el vector y devuelve el numero de componentes en util_array
 * @param array vector de entrada/salida
 * @param util_array
 */
void leer(double array[], int &util_array);
/**
@brief Escribe la longitud y los elementos del array en la salida estándar
@param array El array a imprimir
@param util_array Número de elementos útiles en el array
@pre array puede no contener ningun elemento
*/
void imprimirArray(const double array[],int util_array);

/**
 * @brief un método de ordenacion que reciba 
 * @param v vector de double
 * @param util_v entero numero de elementos utiles
 * @param asc bool ascendente, false si es descendente
 */
void ordenar(double v[], int util_v, bool asc);

/**
 * @brief devuelve sobre el mismo vector el resultado sin valores repetidos
 * @param array1 vector de entrada/salida 
 * @param utilArray1 numero de componentes actuales de salida
 */
void unico (double array1[], int &utilArray1);

/**
 * @brief concatena en un tercer vector  el contenido de dos arrays
 * @param array1 vector de entrada
 * @param utilArray1
 * @param array2 vector de entrada
 * @param utilArray2
 * @param arraySalida vector de salida
 * @param util_salida numero de componentes de vector arraySalida,  de salida
 */
void concatenar( double array1[], int utilArray1,  double array2[], int utilArray2, double arraySalida[], int &util_salida);

/**
 * @brief Realiza una mezcla sin introducir elementos comunes en arraySalida
 * @param array1 vector de entrada
 * @param utilArray1
 * @param array2 vector de entrada
 * @param utilArray2
 * @param arraySalida vector de salida
 * @param util_salida de salida
 * @pre los dos arrays deben estar ordenados
 */
void  mezclarUnico(double array1[], int utilArray1, double array2[], int utilArray2, double arraySalida[], int &util_salida);

#endif

