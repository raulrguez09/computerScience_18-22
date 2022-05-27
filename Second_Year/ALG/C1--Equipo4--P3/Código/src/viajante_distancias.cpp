/*  Grupo C1-4:
    Antonio Lorenzo Gavilán Chacón
    Inés Nieto Sánchez
   	Raúl Rodríguez Pérez
	Francisco Javier Gallardo Molina

Asignatura Algoritmica (ALG)
practica 3: greedy (voraz)
Version:0.1

EJERCICIO Comerciante de comercio (TSP) Algoritmo basado en aristas.
Dado un conjunto de ciudades y una matriz con las distancias entre todas ellas, un viajante debe recorrer
todas las ciudades exactamente una vez, regresando al punto de partida, de forma tal que la distancia
recorrida sea mínima.
Mas formalmente, dado un grafo G, conexo y ponderado, se trata de hallar el ciclo hamiltoniano de mínimo
peso de ese grafo.
Este algoritmo está implementado por nosotros, en el cuál creamos un map ( map<int , pair<int, int> >
aristas) formado por la distancia entre dos ciudades cada entrada.
Vamos seleccionando las distancias menores entre dos ciudades y añadiendo estas al conjunto de
seleccionados. Para poder insertar una nueva ciudad, esta no puede tener más de 2 aristas ni crear un ciclo.
Como el camino resultante de este algoritmo no es cerrado, tenemos que recorrer el camino y añadir la
distancia entre las 2 ciudades que únicamente tienen una arista.
*/

//compilar: g++ viajante_distancias.cpp -o viajante_distancias
//ejecutar: ./viajante_distancias archivo.tsp

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <iomanip>      // std::setw
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <list>
using namespace std;

//////////////////////////////////////////////////////////////

// Comprueba si existe un fichero
//
// Recibe:          nombre, nombre del fichero a buscar
//
// Devuelve:        true si esxiste el fichero

bool ExisteFichero (const string &nombre)
{
    ifstream fichero;
    bool problema;
    fichero.open (nombre.c_str());
    problema = fichero.fail();
    if (!problema) fichero.close();
    return ((problema) ? false : true);
}

void leer_puntos(string & nombre, map<int, pair<double, double> > & M) {
    ifstream datos;
    pair<double,double> p;
    int act;

    if (!ExisteFichero(nombre)) {
        cerr << "\nError: no puedo abrir " << nombre << "\n\n";
        exit (1);
    }

    datos.open(nombre.c_str());

    if (!datos) {
        cerr << "Error: no puedo abrir " << nombre << endl;
        exit (3);
    }

    const int MAX = 500;
	char cad[MAX];		// Para leer cada una de las lineas iniciales

	int num_linea = 1;	// Contador de líneas leidas
    int num_lineas_iniciales = 6;
    datos.getline (cad, MAX); // Lectura adelantada de una línea

    while (num_linea < num_lineas_iniciales) {

		num_linea++;
		datos.getline (cad, MAX); // Lectura de una nueva linea
	}
  if(cad[0]!='N'){
    datos.getline(cad, MAX);
  }
    while (datos >> act) {
        datos >> p.first >> p.second;
        M[act] = p;
    }

    datos.close();
}



//mostrar matriz
void mostrar (const vector< vector<int> > & m) {
    cout<<"la matriz es:"<<endl;
    cout<<setw(3);
    for(int i=0; i<m.size(); i++) {
        cout<<"Ciudad "<<i+1<<": "<<endl;
        for(int j=0; j<m[i].size(); j++)
            cout<<m[i][j]<<" ";
        cout<<endl;
        cout<<endl;
    }
}
//calcular distancia
int euclides (double xi,double yi,double xj,double yj) {
    double aux1=(xj-xi)*(xj-xi);
    double aux2=(yj-yi)*(yj-yi);
    aux2=aux1+aux2;
    int aux=sqrt(aux2);
    return aux;

}
//creamos la matriz de distancias
//Asignamos a la distnacia entre la misma ciudad como -1.
void calcular_matriz(map<int, pair<double, double> >  m,vector< vector<int> > & matriz) {
    for(int i=0; i<matriz.size(); i++) {
        for(int j=0; j<matriz[i].size(); j++){
            if(i!=j) {
                matriz[i][j]=euclides(m[i+1].first,m[i+1].second,m[j+1].first,m[j+1].second);
            }
            else
                matriz[i][j] = -1;
        }
    }
}


void mostrar(multimap<int , pair<int,int> > & a) {
    multimap<int , pair<int,int> >::iterator it=a.begin();
    for(; it!=a.end(); it++) {
        cout<<(*it).first<<"  "<<((*it).second).first<<"   "<<((*it).second).second<<endl;
    }
}
void mostrar(list< pair<int,int> > & a) {
    list <pair<int,int> >::iterator it=a.begin();
    for(; it!=a.end(); it++) {
        cout<<(*it).first<<"  "<<(*it).second<<endl;
    }

}

// Calcula las posibles aristas y sus distancias
multimap<int , pair<int,int> > calcular_aristas(const vector< vector<int> > & m) {
    multimap<int , pair<int,int> > a;
    for(int i=0; i<m.size(); i++) {
        for(int j=0; j<m[i].size(); j++) {
            if(j>i) {
                a.insert(pair<int, pair<int,int> >(m[i][j],pair<int,int>(i+1,j+1)));
            }
        }
    }
    return a;
}

//comprueba si es factible añadir un nodo.
//si un vertice tienes mas de dos arista
bool factible( list<pair<int,int> > & aux, const pair<int,int> & s) {
    int A=s.first,B=s.second,contA=0,contB=0;
    list<pair<int,int> >::iterator it=aux.begin();
    for(; it!=aux.end(); it++) {
        if(A==(*it).first or A==(*it).second) contA++;
        if(B==(*it).first or B==(*it).second) contB++;
    }
    return !(contA>1 or contB>1);
}



list<pair<int,int> >::iterator buscar2(list<pair<int,int> >& aux,int  obj) {
    list<pair<int,int> >::iterator it;
    for(it=aux.begin(); it!=aux.end(); it++) {
        if((*it).first==obj) {
            return it;
        }
        else if((*it).second==obj) {
            return it;
        }
    }
    return aux.end();
}
//si al añadirle el nodo s, todos tiene dos aristas, se crea un ciclo
bool hayciclos(list<pair<int,int> > aux, const pair<int,int> & s) {
    int pos,res;
    list<pair<int,int> >::iterator it;
    res=s.second;
    pos=s.first;
    it=buscar2(aux,pos);
    while(it!=aux.end()) {
        if(pos==(*it).first) pos=(*it).second;
        else pos=(*it).first;
        aux.erase(it);
        it=buscar2(aux,pos);
    }
    return pos==res;
}


list<pair<int,int> >::iterator buscar(list<pair<int,int> >& aux,int & obj) {
    list<pair<int,int> >::iterator it;
    for(it=aux.begin(); it!=aux.end(); it++) {
        if((*it).first==obj) {
            obj=(*it).second;

            return it;
        }
        else if((*it).second==obj) {
            obj=(*it).first;

            return it;
        }
    }
}
vector <int> camino(list <pair<int,int> >aux) {
    vector<int>c;
    list <pair<int,int> >::iterator it=aux.begin();
    c.push_back((*it).first);
    int obj=(*it).second;
    aux.erase(it);
    while(!aux.empty()) {
        c.push_back(obj);
        it=buscar(aux,obj);
        aux.erase(it);
    }
    c.push_back(c.front());
    return c;
}

//cuando ya solo falta un nodo, lo introducimos en el camino y cerramos el ciclo.
void cerrar_ciclo(list <pair<int,int> > & aux,multimap<int, pair<int,int> > & a,int & d) {
    int falta1=0,falta2=0,contadorA=0,contadorB=0;
    list<pair<int,int> >::iterator it1,it2;
    for(it1=aux.begin(); it1!=aux.end(); it1++) {
        for(it2=aux.begin(); it2!=aux.end(); it2++) {
            if((*it1).first==(*it2).first or (*it1).first==(*it2).second) contadorA++;
            if((*it1).second==(*it2).first or (*it1).second==(*it2).second) contadorB++;
            if(contadorA==2 and contadorB==2) break;
        }
        if(contadorA<2 and falta1==0) falta1=(*it1).first;
        else	if(contadorA<2 and falta2==0) falta2=(*it1).first;
        if(contadorB<2 and falta1==0) falta1=(*it1).second;
        else if(contadorB<2 and falta2==0) falta2=(*it1).second;
        contadorA=contadorB=0;
    }
    multimap<int , pair<int,int> >::iterator it;
    for(it=a.begin(); it!=a.end(); it++) {
        if((((*it).second).first==falta1 and ((*it).second).second==falta2)or  (((*it).second).first==falta2 and ((*it).second).second==falta1)) {
            aux.push_back((*it).second);
            d+=(*it).first;
            cout << "La pareja de ciudades que se deben unir para cerrar el ciclo son " << (*it).first << " " << ((*it).second).first << " " << ((*it).second).second;
        }

    }
}

//calcula el recorrido
vector<int> recorrido(multimap<int, pair<int,int> > & a,int & d) {
    vector<int>c;
    list<pair<int,int> > aux;
    multimap<int , pair<int,int> >::iterator it=a.begin();
    aux.push_back((*it).second);
    d+=(*it).first;
    it++;
    while(it!=a.end()) {
        if(factible(aux,(*it).second) and !hayciclos(aux,(*it).second)) {
            aux.push_back((*it).second);
            d+=(*it).first;
        }
        if(!factible(aux,(*it).second)){
          cout << "No es factible: " << (*it).first << " " << ((*it).second).first << " " << ((*it).second).second << endl;
        }
        if(hayciclos(aux,(*it).second)){
          cout << "Hay ciclo: " << (*it).first << " " << ((*it).second).first << " " << ((*it).second).second << endl;
        }
        it++;
    }
    cerrar_ciclo(aux,a,d);
    c=camino(aux);
    return c;
}

//devuelve las ciudades ordenadas con sus coordenadas.
//para poder crear el camino en una grafica
void mostrar_resultado(const vector<int> &result,const map<int,pair<double,double> > &m) {
    vector<int>::const_iterator it;
    for(it=result.begin(); it!=result.end(); it++) {
        pair<double,double> p;
        p=(m.find(*it))->second;
        cout<<*it<<" "<<p.first<<" "<<p.second<<endl;
    }
}

int main(int argc, char * argv[])
{
    multimap<int , pair<int,int> > aristas;
    map<int, pair<double, double> >  m;//un map con las posicion y las dimensiones.
    vector< vector<int> >  matriz;//cremaos un matriz con la distnacia entre dos pueblos
    vector<int> ciudades;
    int tama=0,distancia=0;
    string fp;
    if (argc<2) {
        cout << "Error Formato:  tsp puntos" << endl;
        exit(1);
    }

    fp = argv[1];
    // Se pasan las ciudades y sus dimensiones al map
    leer_puntos(fp,m);
    tama=m.size();
    matriz.resize(tama, vector<int>(tama,-1));

    // Creamos la matriz de distancias
    calcular_matriz(m,matriz);
    //mostrar(matriz);

    aristas=calcular_aristas(matriz);

    // Obtenemos la lista con las ciudades obtenidas
    ciudades=recorrido(aristas,distancia);

    // Se muestra la distancia total obtenida y el orden de las ciudades
    // cout<<"La distancia total es: "<<distancia<<" y el orden de las ciudades es:"<<endl;
    // for(int i=0; i<ciudades.size(); i++) cout<<ciudades[i]<<"   ";
    // cout<<endl<<endl;

    // Se muestran las ciudades en orden junto con sus coordenadas
    mostrar_resultado(ciudades,m);

    return 0;
}
