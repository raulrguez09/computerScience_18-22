//Alumno 1: Fernández Jiménez, Cristian.


/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   utilidades.h
 * Author: Cristian Fernández 
 *
 * Created on 2 de abril de 2019, 12:07
 */

#ifndef UTILIDADES_H
#define UTILIDADES_H


/**
@brief Escribe la longitud y los elementos de la cadena en la salida estándar
@param cadena La cadena a imprimir
@param util_cadena Número de elementos útiles en la cadena
*/
void imprimirCadena(const char cadena[],int util_cadena);


/**
 * @brief Devuelve la longititud de la cadena introducida
 * @param cadena
 * @return longitud de la cadena
 */
int longitud(const char cadena[]);

/**
 * @brief Comprueba si la segunda cadena está contenida en la primera.
 * @param cadena
 * @param subcadena
 * @return Posición dónde comienza la subcadena. Si devuelve -1, no se encuentra contenida.
 */
int localizarSubcadena(const char cadena[], const char subcadena[]);


#endif /* UTILIDADES_H */

