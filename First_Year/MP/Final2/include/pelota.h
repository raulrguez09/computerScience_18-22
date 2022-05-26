/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   pelota.h
 * Author: cristian
 *
 * Created on 15 de mayo de 2019, 0:30
 */

//Alumno 1: Fernández Jiménez, Cristian
//Alumno 2: Crespo Arco, Cristina María


#ifndef PELOTA_H
#define PELOTA_H





class Pelota{
private:
  float x,y;
  float dx, dy;
  float radio=RADIO;
  PColor color;
  
public:
   /**
    * @brief Constructor random (COLOR POR DEFECTO VERDE, PARA FACILITAR LAS PARTIDAS)
    */
    Pelota();
    
    /**
     * @brief Constructor con posiciones dadas y resto random
     * @param X
     * @param Y
     */
    Pelota(float X, float Y);
    
    /**
     * @brief Constructor con elementos dados menos el radio (cte RADIO)
     * @param X
     * @param Y
     * @param DX
     * @param DY
     * @param COLOR
     */
    
    Pelota(float X, float Y, float DX, float DY, PColor COLOR);
    
    /**
     * @brief Constructor completo
     * @param X
     * @param Y
     * @param DX
     * @param DY
     * @param Radio
     * @param COLOR
     */
    Pelota(float X, float Y, float DX, float DY, float Radio, PColor COLOR);

    /**
     * @brief Modificador de Pelota con el radio fijo
     * @param X
     * @param Y
     * @param DX
     * @param DY
     * @param COLOR
     */
    void setPelota(float X, float Y, float DX, float DY, PColor COLOR);
    
    /**
     * @brief Modificador de todos los elementos de una Pelota
     * @param X
     * @param Y
     * @param DX
     * @param DY
     * @param Radio
     * @param COLOR
     */
    void setPelota(float X, float Y, float DX, float DY, float Radio, PColor COLOR);

    /**
     * @Modificador de posiciones de una Pelota
     * @param X
     * @param Y
     */
    void setPosicion(float X, float Y);
    
    /**
     * @brief Modificador de desplazamientos de una Pelota
     * @param DX
     * @param DY
     */
    void setDesplazamientos(float DX,float DY);
    
    /**
     * @brief Modificador de Color de una Pelota
     * @param COLOR
     */
    void setColor(PColor COLOR);
    
    /**
     * @brief Obtiene la posición X de una Pelota
     * @return Posición X
     */
    float getPosX() const;
    
    /**
     * @brief Obtiene la posición Y de una Pelota
     * @return Posición Y
     */
    float getPosY() const;
    
    /**
     * @brief Obtiene el desplazamiento en el eje X de una Pelota
     * @return Desplazamiento en X
     */
    float getDx() const;
    
    /**
     * @brief Obtiene el desplazamiento en el eje Y de una Pelota
     * @return Desplazamiento en Y
     */
    float getDy() const;
    
    /**
     * @brief Obtiene el Radio de una Pelota
     * @return Radio
     */
    float getRadio() const;
    
    /**
     * @brief Obtiene el color de una Pelota
     * @return Color
     */
    PColor getColor() const; 
    
    /**
     * @brief Compara dos pelotas, según su color y radio
     * @param P
     * @return Iguales o no
     */
    bool operator==(const Pelota &P);
    
    /**
     * @brief Asigna a una pelota todas las características de otra
     * @param P
     */
    void operator=(const Pelota &P);
    
    /**
     * @brief Modifica la posición de la pelota según su desplazamiento
     */
    void mover() ;
    
    /**
     * @brief Sobrecarga del operador de salida para Pelota
     */
    friend std::ostream & operator<<(std::ostream &, const Pelota &);
    
    /**
     * @brief Sobrecarga del operador de entrada para Pelota
     */
    friend std::istream & operator>>(std::istream &,  Pelota &);
   
};


    


#endif /* PELOTA_H */

