//Alumno 1: Fern�ndez Jim�nez, Cristian.
//Alumno 2: Crespo Arco, Cristina Mar�a.

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   utilidades.h
 * Author: Alumno 1 & Alumno 2
 *
 * Created on 19 de marzo de 2019, 12:07
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

