/*  Grupo C1-4:
    Antonio Lorenzo Gavilán Chacón
    Inés Nieto Sánchez
   	Raúl Rodríguez Pérez
	Francisco Javier Gallardo Molina

Asignatura Algoritmica (ALG)
practica 3: greedy (voraz)
Version:0.1

EJERCICIO Viajante de comercio (TSP) vecino mas cercano
Dado un conjunto de ciudades y una matriz con las distancias entre todas ellas, un viajante debe recorrer
todas las ciudades exactamente una vez, regresando al punto de partida, de forma tal que la distancia
recorrida sea mínima.
Mas formalmente, dado un grafo G, conexo y ponderado, se trata de hallar el ciclo hamiltoniano de mínimo
peso de ese grafo.
Primero creamos una matriz con la distancias entre las ciudades, utilizando el algoritmo de Euclides.
Comenzamos seleccionando la ciudad inicial como la 1. Recorremos la fila 1 y seleccionamos la ciudad a
menor distancia (columnas). Cuando hacemos esto saltamos a la fila de la ciudad seleccionada y volvemos a
realizar este procedimiento. Tenemos en cuenta que no podemos introducir ciudades repetidas.
Cuando haya introducido de la lista todas las ciudades sin repeticiones, añadimos a la distancia final el
camino entre la última ciudad y la primera, e insertamos de nuevo la ciudad 1 (única que se repite).
*/

//compilar: g++ viajante_cercanias.cpp -o viajante_cercanias
//ejecutar: ./viajante_cercanias archivo.tsp


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

// Se copian las ciudades y sus coordenadas en el map M
void leer_puntos(string & nombre, map<int, pair<double, double> > & M) {
    ifstream datos;
    pair<double,double> p;
    int act;

    // Comprobar si existe/puede abrirse el fichero

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
    cout<<"La matriz es:"<<endl;
    cout<<setw(3);
    for(int i=0; i<m.size(); i++) {
        //cout<<"Ciudad "<<i+1<<": "<<endl;
        for(int j=0; j<m[i].size(); j++)
            cout<<m[i][j]<<setw(4);
        cout<<endl;
        //cout<<endl;
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
//rellenamos la columna de -1 para que esta no se vuelva a utilizar.
void modificar_columna(vector< vector<int> > & m,int colum) {
    for(int i=0; i<m.size(); i++) {
        for(int j=0; j<m[i].size(); j++)
            if(colum==j) {
                m[i][j]=-1;
            }
    }
}
//tomamos como nodo inicial la ciudad 1.
//entra la matriz
//devolvemos el vector de ciudades cogidas y la distancia.
vector<int> recorrido(vector< vector<int> >  matriz,int & d) {
    vector<int>c;//ciudades selecionadas
    int nodo=0,min=0,pos=0,i=1,j=0;
    //primero introducimos el primero nodo en el vector
    c.push_back(nodo+1);
    for(; i<matriz.size(); i++) { //contador
        j=1;
        while(matriz[nodo][j]==-1) {
            j++;
        }
        min=matriz[nodo][j];
        pos=j;
        for(; j<matriz[nodo].size(); j++) {
            if(matriz[nodo][j]!=-1 and min>matriz[nodo][j]) {
                min=matriz[nodo][j];
                pos=j;
            }
        }
        nodo=pos;
        c.push_back(nodo+1);
        modificar_columna(matriz,nodo);
        d+=min;
    }
    //añadirle la distnacia del ultimo nodo al inicio
    d+=matriz[nodo][0];
    //le añadimos de nuevo el nodo 1..
    c.push_back(1);
    return c;
}

//devuelve las ciudades ordenadas con sus coordenadas.
//para poder crear el camino en una grafica
void mostrar_resultado(const vector<int> &result,const map<int,pair<double,double> > &m) {
    for(int i=0; i<result.size(); i++) {
        pair<double,double> p;
        p=(m.find(result[i]))->second;
        cout<<result[i]<<" "<<p.first<<" "<<p.second<<endl;
    }
}

void salidaEstandar(const vector<int> &result,const map<int,pair<double,double> > &m){
	pair<double,double> par;
	par=(m.find(result[0]))->second;
	cout<<"La primera ciudad es: "<<result[0]<<" "<<par.first<<" "<<par.second<<endl;
	par=(m.find(result[1]))->second;
	cout<<"La ciudad vecina de la ciudad "<< result[0] <<" es: "<<result[1]<<" "<<par.first<<" "<<par.second<<endl;

}

int main(int argc, char * argv[])
{

    // Declaración de variables
    map<int, pair<double, double> >  m;     //un map con las posicion y las dimensiones.
    vector< vector<int> >  matriz;          //cremaos un matriz con la distancia entre dos pueblos
    vector<int> ciudades;
    int tam = 0,distancia = 0;
    string fp;
    if (argc<2) {
        cerr << "Formato " << argv[0] << " archivo.tsp" << endl;
        exit(EXIT_FAILURE);
    }

    fp = argv[1];
    // Se pasan las ciudades y sus dimensiones al map
    leer_puntos(fp,m);
    tam = m.size();
    matriz.resize(tam, vector<int>(tam,-1));

    // Creamos la matriz de distancias
    calcular_matriz(m,matriz);

    // Obtenemos el vector con las ciudades obtenidas
    ciudades=recorrido(matriz,distancia);

    // Se muestra la distancia total obtenida y el orden de las ciudades
    cout<<"La distancia total es: " << distancia << " y el orden de las ciudades es:" << endl;
    for(int i = 0; i < ciudades.size(); i++) cout << ciudades[i] << "   ";
    cout<<endl<<endl;

		//Mostramos la primera ciudad y su ciudad vecina
		//salidaEstandar(ciudades,m);
		//cout << endl;

		// Mostramos la matriz de distancias
		//mostrar(matriz);

		//Mostramos el recorrido final. Se muestran las ciudades en orden junto con sus coordenadas
    //cout << "Recorrido final: " << endl;
    mostrar_resultado(ciudades,m);
    //cout<<endl;
    //cout<<"La distancia total es: "<<distancia<<endl;

    return 0;
}
