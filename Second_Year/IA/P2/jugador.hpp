#ifndef COMPORTAMIENTOJUGADOR_H
#define COMPORTAMIENTOJUGADOR_H

#include "comportamientos/comportamiento.hpp"

#include <list>

struct estado {
  int fila;
  int columna;
  int orientacion;
};

//Nodo empleado en la busqueda de costo uniforme
struct nodo_unif{
	estado st;
	list<Action> secuencia;
	bool zapatillas;			
	bool bikini;				
	int coste;					
};

class ComportamientoJugador : public Comportamiento {
  public:
    ComportamientoJugador(unsigned int size) : Comportamiento(size) {
      // Inicializar Variables de Estado
      fil = col = 99;
      brujula = 0; // 0: Norte, 1:Este, 2:Sur, 3:Oeste
      destino.fila = -1;
      destino.columna = -1;
      destino.orientacion = -1;
      hayplan=false;
      bikini = false;
      zapatillas = false;
      bateria.fila = -1;
      bateria.columna = -1;
    }
    
    ComportamientoJugador(std::vector< std::vector< unsigned char> > mapaR) : Comportamiento(mapaR) {
      // Inicializar Variables de Estado
      fil = col = 99;
      brujula = 0; // 0: Norte, 1:Este, 2:Sur, 3:Oeste
      destino.fila = -1;
      destino.columna = -1;
      destino.orientacion = -1;
      hayplan=false;
      bikini = false;
      zapatillas = false;
      bateria.fila = -1;
      bateria.columna = -1;
    }
    ComportamientoJugador(const ComportamientoJugador & comport) : Comportamiento(comport){}
    ~ComportamientoJugador(){}

    Action think(Sensores sensores);
    int interact(Action accion, int valor);
    void VisualizaPlan(const estado &st, const list<Action> &plan);
    ComportamientoJugador * clone(){return new ComportamientoJugador(*this);}
    int costeAvanzarNodo(nodo_unif &actual);

  private:
    // Declarar Variables de Estado
    int fil, col, brujula;
    estado origen, destino, bateria;
    list<Action> plan;
    bool hayplan;
    bool bikini;
    bool zapatillas;
    const int recarga = 1500;
    const int bateriaBaja = 1000;
    const int maxBateria = 3000;

    // Métodos privados de la clase
    bool pathFinding(int level, const estado &origen, const estado &destino, list<Action> &plan);
    bool pathFinding_Profundidad(const estado &origen, const estado &destino, list<Action> &plan);
    bool pathFinding_Anchura(const estado &origen, const estado &destino, list<Action> &plan);
    bool pathFinding_CosteUniforme(const estado &origen, const estado &destino, list<Action> &plan);
    void RellenarMapaResultado(vector<vector<unsigned char> > &m, const Sensores & sen);
    
    //Métodos relacionados con la bateria y su recarga
    bool necesitoRecargar(const Sensores & sensores);
    bool casillaBateria();
    void recargar(const Sensores & sensores);
    void irACasillaRecarga(const Sensores & sensores);

    void PintaPlan(list<Action> plan);
    bool HayObstaculoDelante(estado &st);
};

#endif
