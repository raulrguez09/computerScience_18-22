#ifndef _PUNTO_H
#define _PUNTO_H

/// Clase Punto
class Punto {
private:
    double x; ///< coordenada x del punto
    double y; ///< coordenada y del punto};
public:
    Punto(){x=0;y=0;} ///< constructor. Pone a 0 las dos coordenadas
    Punto(double _x, double _y){x=_x; y=_y;}///< constructor. Inicializa un punto con dos valores x y
    double getX() const {return x;} ///< Devuelve la coordenada x del punto
    double getY() const {return y;} ///< Devuelve la coordenada y del punto
    void setX(double nuevoX); ///< Asigna el valor nuevoX a la coordenada x del punto
    void setY(double nuevoY); ///< Asigna el valor nuevoY a la coordenada y del punto
    void escribir() const; ///<  Escribe un punto en formato (x,y)
    void leer(); ///< // Lee un punto en el formato (x,y)
};

/// Funciones auxiliares (no son métodos de la clase)


/**
@brief Calcula la distancia entre dos puntos
@param p1 primer punto
@param p2 segundo punto
@return la distancia entre el punto @a p1 y el punto @a p2
*/

double distancia(Punto p1, Punto p2);

/**
@brief Calcula el punto que está entre dos puntos dados con distancia mínima a ambos
@param p1 primer punto
@param p2 segundo punto
@return un punto entre el punto @a p1 y el punto @a p2 con distancia mínima a ambos
*/
Punto puntoMedio(Punto p1, Punto p2);
#endif

