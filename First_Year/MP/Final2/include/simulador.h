/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   simulador.h
 * Author: cristian
 *
 * Created on 15 de mayo de 2019, 0:30
 */

//Alumno 1: Fernández Jiménez, Cristian
//Alumno 2: Crespo Arco, Cristina María


#ifndef SIMULADOR_H
#define SIMULADOR_H

class Simulador{
private: 
    int ancho, alto;
    Pelotas original;
    Pelotas actual;
public:
    /**
     * @brief Construye la ventana e inicializa los conjuntos de Pelotas según un archivo, realizando las definidas comprobaciones
     * @param fichero (HA DE TENER LA CABECERA "MP-PELOTAS-T-1.0")
     */
    Simulador(std::string fichero);
    
    /**
     * @brief Cierra la ventana y libera los conjuntos de Pelotas
     */
    ~Simulador();
    
    /**
     * @brief Mueve el conjunto actual un número de veces además de colisionar las pelotas según las reglas propuestas
     * @param n
     */
    void step (int n);
    
    /**
     * @brief Escribe sobre el fichero dado el resultado final del conjunto de actual, además de la información de la ventana y la cabecera de lectura
     * @param fichero
     * @return 
     */
    bool salvar(std::string fichero);
    
    /**
     * @brief Obtiene el conjunto actual de Pelotas, solo permite lectura
     * @return actual (cte)
     */
    const Pelotas& getActual() const;
    
    /**
     * @brief Obtiene el conjunto original de Pelotas, solo permite lectura
     * @return original (cte)
     */
    const Pelotas& getOriginal() const;
    
    /**
     * @brief Obtiene el conjunto actual de Pelotas, con posibilidad de editarlo
     * @return actual
     */
    Pelotas & getActual();
    
};


#endif /* SIMULADOR_H */

