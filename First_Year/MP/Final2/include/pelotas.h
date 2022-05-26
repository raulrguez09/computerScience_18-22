/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   pelotas.h
 * Author: cristian
 *
 * Created on 15 de mayo de 2019, 0:30
 */

//Alumno 1: Fernández Jiménez, Cristian
//Alumno 2: Crespo Arco, Cristina María


#ifndef PELOTAS_H
#define PELOTAS_H



class Pelotas{
private: 
    Pelota *v;
    int capacidad;
    int util;
public:
    /**
     * @brief Constructor por defecto, reserva espacio para una Pelota
     */
    Pelotas();
    
    /**
     * @brief Constructor que reserva espacio para npelotas
     * @param npelotas
     */
    Pelotas(int npelotas);
    
    /**
     * @brief Constructor que calca un conjunto dado, reservando el espacio necesario
     * @param original
     */
    Pelotas(const Pelotas &original);
    
    /**
     * @brief Destructor del conjunto, que libera la memoria reservada
     */
    ~Pelotas();
    
    /**
     * @brief Obtiene la capacidad del conjunto de Pelotas
     * @return Capacidad
     */
    int getCapacidad() const;
    
    /**
     * @brief Obtiene el número de Pelotas utiles del conjunto
     * @return Util
     */
    int getUtil() const;
    
    /**
     * @brief Obtiene una pelota del conjunto según la posición dada, la devuelve de forma constante
     * @param pos
     * @return Pelotas[pos] (cte)
     */
    Pelota& get(int pos) const;
    
    /**
     * @brief Borra la pelota de la posición dada
     * @param pos
     */
    void borrar(int pos);
    
    /**
     * @brief Se añade una Pelota al conjunto, al final, realojando si es necesario
     * @param p
     */
    void aniadir(const Pelota &p);
    
   
    /**
     * @brief Permite añadir una pelota al conjunto mediante el operador +=
     * @param p
     */
    void operator+=(const Pelota &p);
    
    /**
     * @brief Se obtiene la Pelota de la posición dada y es posible editarla
     * @param pos
     * @return Pelota[pos]
     */
    Pelota& obtener(int pos);
    
    /**
     * @brief Mueve todas las pelotas del conjunto
     */
    void mover();
    
    /**
     * @brief Colisiona las pelotas de un mismo conjunto
     */
    void colisionarPelotas();
    
    /**
     * @brief Colisiona las pelotas del conjunto según las reglas propuestas
     */
    void colisionarJuego();
     
    /**
     * @brief Sobrecarga del operador de salida, para un conjunto de Pelotas
     * @param original
     */
    friend std::ostream & operator<<(std::ostream &, const Pelotas &);
     
    /**
     * @brief Sobrecarga del operador de entrada, para un conjunto de Pelotas
     * @param original
     */
    friend std::istream & operator>>(std::istream &,  Pelotas &);
     
    /**
     * @brief Asigna a un conjunto de Pelotas otro conjunto dado, reservando memoria suficiente para este
     * @param original
     */
    void operator=(const Pelotas &original);
     
    /**
     * @brief Operador de indexación, permite editar
     * @param i
     * @return Pelota[i]
     */
    Pelota& operator[](int i);
     
     
    /**
     * @brief Operador de indexación constante, solo permite leer
     * @param i
     * @return Pelota[i] (cte)
     */
    Pelota& operator[](int i) const;

    
};


#endif /* PELOTAS_H */

