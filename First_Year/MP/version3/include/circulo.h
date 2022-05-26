#ifndef _CIRCULO_H
#define _CIRCULO_H
#include "punto.h"
/// Clase Circulo

class Circulo {
private:
    Punto centro; ///< Centro del círculo
    double radio; ///< radio del círculo
public:
    Circulo(); ///< Constructor: Pone a 0 el punto y el radio
    Circulo(Punto centro, double radio); ///< Constructor: Inicializa el círculo con un centro y un radio
    void set(Punto centro, double radio); ///< Asigna el centro y el radio a un circulo
    Punto getCentro() const; ///< Devuelve el centro de un circulo
    double getRadio() const; ///< Devuelve el radio de un circulo
    void escribir() const; ///< Escribe círculo en formato radio-centro
    void leer(); ///< lee círculo en formato radio-centro
    double area() const; ///< Devuelve el área de un círculo
};

/// Funciones auxiliares


/**
@brief Calcula la distancia entre dos circulos
@param c1 primer círculo
@param c2 segundo círculo
@return la distancia entre el círculo @a c1 y el círculo @a c2

La distancia entre dos círculos se define como la distancia entre los centros menos los dos radios.
Nótese que la distancia puede ser negativa si los círculos se intersecan
*/

double distancia (Circulo c1, Circulo c2);

/**
@brief Comprueba si un punto es interior a un círculo
@param p punto a comprobar
@param c circulo
@retval true si el punto @a p es interior al círculo @a c
@retval false en caso contrario
*/

bool interior (Punto p, Circulo c);
#endif
