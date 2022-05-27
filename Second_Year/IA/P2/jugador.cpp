#include "../Comportamientos_Jugador/jugador.hpp"
#include "motorlib/util.h"

#include <iostream>
#include <cmath>
#include <set>
#include <queue>
#include <stack>

// Este es el método principal que debe contener los 4 Comportamientos_Jugador
// que se piden en la práctica. Tiene como entrada la información de los
// sensores y devuelve la acción a realizar.
Action ComportamientoJugador::think(Sensores sensores) {	
	fil = sensores.posF;
	col = sensores.posC;
	brujula = sensores.sentido;

	RellenarMapaResultado(mapaResultado,sensores);	

	if (!hayplan or plan.empty()){
		estado origen;
		origen.fila = fil;
		origen.columna = col;
		origen.orientacion = brujula;

		destino.fila = sensores.destinoF;
		destino.columna = sensores.destinoC;

		if (sensores.nivel == 4 and necesitoRecargar(sensores) and casillaBateria()){
			cout << "necesito recargar y tengo la ubicacion" << endl;
			if (origen.fila != bateria.fila && origen.columna != bateria.columna){
				cout << "voy a la casilla de recarga" << endl;
 				irACasillaRecarga(sensores);
			}
			else{
				cout << "voy a recargar" << endl;
				recargar(sensores);
			}
		}
		else{
			hayplan = pathFinding(sensores.nivel, origen, destino,plan);
		}
	}
	
	Action sigAccion;
	if (hayplan and plan.size()>0){
		sigAccion = plan.front();
		plan.erase(plan.begin());
	}

	if((sensores.terreno[2]=='P' or sensores.terreno[2]=='M' or sensores.superficie[2]=='a') and sigAccion == actFORWARD){
		hayplan = false;
		return Action::actIDLE;
	}
	
	// Parte de pruebas para mapas mas grandes, recalcular siempre para no ir por sitios con
	// mucho coste (descomentar para obtener mejores resultados en mapas grandes)
	//
	// if((sensores.terreno[2]=='A' or sensores.terreno[2]=='B') and sigAccion == actFORWARD){
	// 	hayplan = false;
	// 	return Action::actFORWARD;
	// }

	return sigAccion;
}

//----------------------------------FUNCIONES AUXILIARES----------------------------------//

void ComportamientoJugador::RellenarMapaResultado(vector<vector<unsigned char> > &m, const Sensores & sen){
  m[sen.posF][sen.posC]=sen.terreno[0];
  int pos = 1;
	switch (sen.sentido) {
		case 0: //Norte
		  for (int i=1; i<4; i++){
				for (int j=-i;j<=i;j++){
					m[(sen.posF)-i][(sen.posC)+j] = sen.terreno[pos];
					pos++;
				}
			}
		break;
		case 1: //Este
		  for (int i=1; i<4; i++){
				for (int j=-i;j<=i;j++){
					m[(sen.posF)+j][(sen.posC)+i] = sen.terreno[pos];
					pos++;
				}
			}
		break;
		case 2: //Sur
		  for (int i=1; i<4; i++){
				for (int j=-i;j<=i;j++){
					m[(sen.posF)+i][(sen.posC)-j] = sen.terreno[pos];
					pos++;
				}
			}
		break;
		case 3: //Oeste
		  for (int i=1; i<4; i++){
				for (int j=-i;j<=i;j++){
					m[(sen.posF)-j][(sen.posC)-i] = sen.terreno[pos];
					pos++;
				}
			}
		break;
	}
}

// Llama al algoritmo de busqueda que se usará en cada comportamiento del agente
// Level representa el comportamiento en el que fue iniciado el agente.
bool ComportamientoJugador::pathFinding (int level, const estado &origen, const estado &destino, list<Action> &plan){
	switch (level){
		case 1: cout << "Busqueda en profundad\n";
			      return pathFinding_Profundidad(origen,destino,plan);
						break;
		case 2: cout << "Busqueda en Anchura\n";
			      return pathFinding_Anchura(origen, destino, plan);
						break;
		case 3: cout << "Busqueda Costo Uniforme\n";
				  return pathFinding_CosteUniforme(origen, destino, plan);
						break;
		case 4: cout << "Busqueda para el reto\n";
				  return pathFinding_CosteUniforme(origen, destino, plan);
						break;
	}
	cout << "Comportamiento sin implementar\n";
	return false;
}

//---------------------- Funciones para bateria ---------------------------//

// Verdadero si la bateria está por debajo del minimo
bool ComportamientoJugador::necesitoRecargar(const Sensores & sensores){
	return sensores.bateria < bateriaBaja;
}

// Verdadero si la posicion de la bateria no es nula
bool ComportamientoJugador::casillaBateria(){
	return bateria.fila != -1 or bateria.columna != -1;
}

// Si el jugador se encuentra en la casilla de recarga
// genera un plan para estar sobre la casilla de recarga hasta agotar el tiempo
// de recarga o hasta que tenga la bateria completamente llena
void ComportamientoJugador::recargar(const Sensores & sensores){									
		int tiempo_recarga = recarga;
		tiempo_recarga /= 10;
		plan.clear();
		for (int i = 0; i < tiempo_recarga; ++i)
			plan.push_back(Action::actIDLE);					
}

// Si sabemos donde está la batería generamos un plan para ir a ella
// en otro caso vamos al destno original
void ComportamientoJugador::irACasillaRecarga(const Sensores & sensores){
	estado origen;
	origen.fila = fil;
	origen.columna = col;
	origen.orientacion = brujula;
	hayplan = pathFinding(sensores.nivel, origen, bateria, plan);
}

//----------------------------------IMPLEMENTACION DE ALGORITMOS DE BÚSQUEDA----------------------------------//

//---------------------- Busqueda en profundidad ---------------------------//

// Dado el código en carácter de una casilla del mapa dice si se puede
// pasar por ella sin riegos de morir o chocar.
bool EsObstaculo(unsigned char casilla){
	if (casilla=='P' or casilla=='M')
		return true;
	else
	  return false;
}

// Comprueba si la casilla que hay delante es un obstaculo. Si es un
// obstaculo devuelve true. Si no es un obstaculo, devuelve false y
// modifica st con la posición de la casilla del avance.
bool ComportamientoJugador::HayObstaculoDelante(estado &st){
	int fil=st.fila, col=st.columna;

  // calculo cual es la casilla de delante del agente
	switch (st.orientacion) {
		case 0: fil--; break;
		case 1: col++; break;
		case 2: fil++; break;
		case 3: col--; break;
	}

	// Compruebo que no me salgo fuera del rango del mapa
	if (fil<0 or fil>=mapaResultado.size()) return true;
	if (col<0 or col>=mapaResultado[0].size()) return true;

	// Miro si en esa casilla hay un obstaculo infranqueable
	if (!EsObstaculo(mapaResultado[fil][col])){
		// No hay obstaculo, actualizo el parámetro st poniendo la casilla de delante.
    st.fila = fil;
		st.columna = col;
		return false;
	}
	else{
	  return true;
	}
}

struct nodo{
	estado st;
	list<Action> secuencia;
};

struct ComparaEstados{
	bool operator()(const estado &a, const estado &n) const{
		if ((a.fila > n.fila) or (a.fila == n.fila and a.columna > n.columna) or
	      (a.fila == n.fila and a.columna == n.columna and a.orientacion > n.orientacion))
			return true;
		else
			return false;
	}
};

// Implementación de la búsqueda en profundidad.
// Entran los puntos origen y destino y devuelve la
// secuencia de acciones en plan, una lista de acciones.
bool ComportamientoJugador::pathFinding_Profundidad(const estado &origen, const estado &destino, list<Action> &plan) {
	//Borro la lista
	cout << "Calculando plan\n";
	plan.clear();
	set<estado,ComparaEstados> generados; // Lista de Cerrados
	stack<nodo> pila;											// Lista de Abiertos

    nodo current;
	current.st = origen;
	current.secuencia.empty();

	pila.push(current);

  while (!pila.empty() and (current.st.fila!=destino.fila or current.st.columna != destino.columna)){

		pila.pop();
		generados.insert(current.st);

		// Generar descendiente de girar a la derecha
		nodo hijoTurnR = current;
		hijoTurnR.st.orientacion = (hijoTurnR.st.orientacion+1)%4;
		if (generados.find(hijoTurnR.st) == generados.end()){
			hijoTurnR.secuencia.push_back(actTURN_R);
			pila.push(hijoTurnR);

		}

		// Generar descendiente de girar a la izquierda
		nodo hijoTurnL = current;
		hijoTurnL.st.orientacion = (hijoTurnL.st.orientacion+3)%4;
		if (generados.find(hijoTurnL.st) == generados.end()){
			hijoTurnL.secuencia.push_back(actTURN_L);
			pila.push(hijoTurnL);
		}

		// Generar descendiente de avanzar
		nodo hijoForward = current;
		if (!HayObstaculoDelante(hijoForward.st)){
			if (generados.find(hijoForward.st) == generados.end()){
				hijoForward.secuencia.push_back(actFORWARD);
				pila.push(hijoForward);
			}
		}

		// Tomo el siguiente valor de la pila
		if (!pila.empty()){
			current = pila.top();
		}
	}

  cout << "Terminada la busqueda\n";

	if (current.st.fila == destino.fila and current.st.columna == destino.columna){
		cout << "Cargando el plan\n";
		plan = current.secuencia;
		cout << "Longitud del plan: " << plan.size() << endl;
		PintaPlan(plan);
		// ver el plan en el mapa
		VisualizaPlan(origen, plan);
		return true;
	}
	else {
		cout << "No encontrado plan\n";
	}


	return false;
}


//------------------------- Busqueda en anchura ---------------------------//

// Implementación de la búsqueda en anchura.
// Entran los puntos origen y destino y devuelve la
// secuencia de acciones en plan, una lista de acciones.
bool ComportamientoJugador::pathFinding_Anchura(const estado &origen, const estado &destino, list<Action> &plan){
	cout << "Calculando plan\n";
	plan.clear();

	set<estado, ComparaEstados> explorados;  //Lista de cerrados
	queue<nodo> frontera;					 //Lista de abiertos

	nodo actual;
	actual.st = origen;
	actual.secuencia.empty();

	frontera.push(actual);					 //La lista de abiertos contiene inicialmente un único elemento, que es el
											 // nodo con el estado inicial

	while (!frontera.empty() and actual.st.fila != destino.fila || actual.st.columna != destino.columna){
		frontera.pop();						 //Quitamos el nodo superficial en frontera
		explorados.insert(actual.st);          //Insertamos el nodo(estado_inicial) en explorados

		//Generamos un hijo descendiente para la acción de girar a la derecha
		nodo hijoDcha = actual;
		hijoDcha.st.orientacion = (hijoDcha.st.orientacion+1)%4;
		if (explorados.find(hijoDcha.st) == explorados.end()){
			hijoDcha.secuencia.push_back(actTURN_R);
			frontera.push(hijoDcha);
		}

		//Generamos un hijo descendiente para la acción de girar a la izquierda
		nodo hijoIzda = actual;
		hijoIzda.st.orientacion = (hijoIzda.st.orientacion+3)%4;
		if (explorados.find(hijoIzda.st) == explorados.end()){
			hijoIzda.secuencia.push_back(actTURN_L);
			frontera.push(hijoIzda);
		}
		
		//Generamos un hijo descendiente para la acción de avanzar
		nodo hijoenFrente = actual;
		if (!HayObstaculoDelante(hijoenFrente.st)){
				if (explorados.find(hijoenFrente.st) == explorados.end()){
					hijoenFrente.secuencia.push_back(actFORWARD);
					frontera.push(hijoenFrente);
			}
		}

		// Elegimos el siguiente valor de nuestra cola/lista de abiertos
		actual = frontera.front();
		while (!frontera.empty() and explorados.find(actual.st) != explorados.end()){
			actual = frontera.front();
			frontera.pop();
		}
 	}

	cout << "Terminada la busqueda\n";
	if (actual.st.fila == destino.fila and actual.st.columna == destino.columna){
		cout << "Cargando el plan\n";
		plan = actual.secuencia;
		cout << "Longitud del plan: " << plan.size() << endl;
		PintaPlan(plan);
		// Visualizamos el plan en el mapa
		VisualizaPlan(origen, plan);
		return true;
	}
	else {
		cout << "No encontrado plan\n";
	}

	return false;
 }

//------------------- Busqueda con coste uniforme ------------------------//

//Calcula y devuelve el coste de un nodo del tipo "nodo_unif"
int ComportamientoJugador::costeAvanzarNodo(nodo_unif &actual){
	int coste = 0;
	char casilla_mapa = mapaResultado[actual.st.fila][actual.st.columna];
	switch (casilla_mapa) {
    case 'B': 
		if (actual.zapatillas)
			coste=5;
		else
			coste=50; 
	break;
    case 'A': 
		if (actual.bikini) 
			coste=10; 
		else 
			coste=100; 
	break;
	case '?': coste=1; 
	break;
    case 'T': coste=2; 
	break;
    case 'S': coste=1; 
	break;
	case 'K': 
		coste = 0; 
		actual.bikini = true;
	break;
	case 'D': 
		coste = 0; 
		actual.zapatillas = true;
	break;
	case 'X':													
			coste = 1;												
			bateria = actual.st;										 
	break;

    default:  coste=1;
  }

	actual.coste += coste;
	return actual.coste;
}

//Struct que compara cuando un nodo_unif es menor a otro
struct comparaCoste{
	bool operator()(const nodo_unif &n1, const nodo_unif &n2) {
		return n1.coste > n2.coste;
	}
};

// Implementación de la búsqueda con coste uniforme.
// Entran los puntos origen y destino y devuelve la
// secuencia de acciones en plan, una lista de acciones.
bool ComportamientoJugador::pathFinding_CosteUniforme(const estado &origen, const estado &destino, list<Action> &plan){
	cout << "Calculando plan\n";
	plan.clear();

	set<estado, ComparaEstados> explorados;      								//Lista de cerrados
	priority_queue<nodo_unif, vector<nodo_unif>, comparaCoste> frontera;		//Lista de abiertos

	nodo_unif actual;
	actual.st = origen;
	actual.secuencia.empty();
	actual.coste = 0;
	actual.bikini = bikini;
	actual.zapatillas = zapatillas;

	frontera.push(actual);					 //La lista de abiertos contiene inicialmente un único elemento, que es el
											 // nodo con el estado inicial

	while (!frontera.empty() and actual.st.fila != destino.fila || actual.st.columna != destino.columna){
		frontera.pop();						
		explorados.insert(actual.st);          //Insertamos el nodo(estado_inicial) en explorados
		
		if(mapaResultado[actual.st.fila][actual.st.columna] == 'K'){
			actual.bikini = true;
		}
		if(mapaResultado[actual.st.fila][actual.st.columna] == 'D'){
			actual.zapatillas = true;
		}
		
		costeAvanzarNodo(actual);

		//Generamos un hijo descendiente para la acción de girar a la derecha
		nodo_unif hijoDcha = actual;
		hijoDcha.st.orientacion = (hijoDcha.st.orientacion+1)%4;
		if (explorados.find(hijoDcha.st) == explorados.end()){
			hijoDcha.secuencia.push_back(actTURN_R);
			frontera.push(hijoDcha);
		}

		//Generamos un hijo descendiente para la acción de girar a la izquierda
		nodo_unif hijoIzda = actual;
		hijoIzda.st.orientacion = (hijoIzda.st.orientacion+3)%4;
		if (explorados.find(hijoIzda.st) == explorados.end()){
			hijoIzda.secuencia.push_back(actTURN_L);
			frontera.push(hijoIzda);
		}
		
		//Generamos un hijo descendiente para la acción de avanzar
		nodo_unif hijoenFrente = actual;
		if (!HayObstaculoDelante(hijoenFrente.st)){
				if (explorados.find(hijoenFrente.st) == explorados.end()){
					hijoenFrente.secuencia.push_back(actFORWARD);
					frontera.push(hijoenFrente);
			}
		}

		// Elegimos el siguiente valor de nuestra cola con prioridad/lista de abiertos
		if(!frontera.empty()){
			actual = frontera.top();
			while(explorados.find(actual.st) != explorados.end()){
				frontera.pop();
				actual = frontera.top();
			}
		}
 	}

	cout << "Terminada la busqueda\n";
	if (actual.st.fila == destino.fila and actual.st.columna == destino.columna){
		cout << "Cargando el plan\n";
		plan = actual.secuencia;
		cout << "Longitud del plan: " << plan.size() << endl;
		PintaPlan(plan);
		// Visualizamos el plan en el mapa
		VisualizaPlan(origen, plan);
		return true;
	}
	else {
		cout << "No encontrado plan\n";
	}

	return false;
}

//----------------------------------FUNCIONES DE AYUDA (PROFESOR)----------------------------------//

// Sacar por la términal la secuencia del plan obtenido
void ComportamientoJugador::PintaPlan(list<Action> plan) {
	auto it = plan.begin();
	while (it!=plan.end()){
		if (*it == actFORWARD){
			cout << "A ";
		}
		else if (*it == actTURN_R){
			cout << "D ";
		}
		else if (*it == actTURN_L){
			cout << "I ";
		}
		else {
			cout << "- ";
		}
		it++;
	}
	cout << endl;
}

void AnularMatriz(vector<vector<unsigned char> > &m){
	for (int i=0; i<m[0].size(); i++){
		for (int j=0; j<m.size(); j++){
			m[i][j]=0;
		}
	}
}

// Pinta sobre el mapa del juego el plan obtenido
void ComportamientoJugador::VisualizaPlan(const estado &st, const list<Action> &plan){
  AnularMatriz(mapaConPlan);
	estado cst = st;

	auto it = plan.begin();
	while (it!=plan.end()){
		if (*it == actFORWARD){
			switch (cst.orientacion) {
				case 0: cst.fila--; break;
				case 1: cst.columna++; break;
				case 2: cst.fila++; break;
				case 3: cst.columna--; break;
			}
			mapaConPlan[cst.fila][cst.columna]=1;
		}
		else if (*it == actTURN_R){
			cst.orientacion = (cst.orientacion+1)%4;
		}
		else {
			cst.orientacion = (cst.orientacion+3)%4;
		}
		it++;
	}
}

int ComportamientoJugador::interact(Action accion, int valor){
  return false;
}
