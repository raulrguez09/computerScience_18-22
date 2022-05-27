#include <chrono>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <string>
#include <utility>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cmath>
#include <climits>
#include <map>
using namespace std;

/* 
Grupo C1-4
Miembros: Raúl Rodríguez Pérez, Antonio Lorenzo Gavilán Chacón, 
          Inés NIeto Sánchez, Francisco Javier Gallardo Molina
Asignatura: Algoritmica (ALG)
Practica 4: Programación Dinámica
Version:0.1

Ejercicio: Resolución del problema del viajante del comercio (TSP) utilizando
           programación dinámica

Compilar: g++ TSP_PD.cpp -o TSP_PD
Ejecutar: ./TSP_PD archivo.tsp
*/


// ExisteFichero -> Comprueba la existencia de un fichero
bool ExisteFichero (const string &nombre)
{
    ifstream fichero;
    bool problema;
    fichero.open (nombre.c_str());
    problema = fichero.fail();
    if (!problema) fichero.close();
    return ((problema) ? false : true);
}

// leer_puntos -> Lee los datos proporcionados por un fichero y los almacena en la matriz
//                pasado por parámetro
void leer_puntos(string &nombre, map<int, pair<double, double> > &M) {
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

// euclides -> Función que cálcula el valor resultante de aplicar la fórmula de euclides
// Empleamos dicha función para calcular la distancia entre ciudades
double euclides(double xi,double yi,double xj,double yj) {
    double aux1=(xj-xi)*(xj-xi);
    double aux2=(yj-yi)*(yj-yi);
    aux2=aux1+aux2;
    double aux=sqrt(aux2);
    return aux;
}

// calcular_matriz -> calculamos la matriz de distancias resultante a partir del mapa que alberga 
//                    las ciudades junto con sus coordenadas
void calcular_matriz(map<int, pair<double, double> >  m,vector< vector<double> > &matriz) {
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

// mostrar_solucion -> Muestra el contenido de la lista de enteros pasada como parámetro
// Empleamos dicha función para mostrar las ciudades una vez calculado el recorrido óptimo final
void mostrar_solucion(const list<int> &res)
{
    auto it = res.cbegin();
    int anterior = *it;
    cout << anterior + 1;
    for (++it; it != res.cend(); ++it)
    {
        cout << " -> " << *it + 1;
        anterior = *it + 1;
    }
}

// g -> función que calcula la distancia min del recorrido partiendo en una ciudad, pasando por todas las demás y 
//      regresando a la primera de nuevo
double g(const vector<vector<double>> &m_dist, int pos, int visitada, vector<vector<double>> &m_sol)
{
    // Si todas las ciudades han sido visitadas, devolvemos la distancia hasta la primera ciudad
    if (visitada == ((1 << m_dist.size()) - 1)){
        return m_dist[pos][0];
    }

    if(m_sol[pos][visitada] >= 0){
        return m_sol[pos][visitada];
    }

    double min = numeric_limits<double>::max();
    // La primera ciudad no se tiene en cuenta así que recorremos el resto de ciudades
    for (int i = 1; i < m_dist.size(); i++){
        // Obtenemos la posición de la ciudad,ya que la primera no se tiene en cuenta, 
        // a la poisicón i le restamos 1
        int pos_visitada = (1 << (i - 1));

        // Evitamos la ciudad que estamos evaluando y las ciudades visitadas
        if (i == pos || ((visitada & pos_visitada) == 0))
            continue;

        // Calculamos la distancia con la fórmula explicada en el pdf (L[i][k] + g(k, S\{k}))
        double distancia = m_dist[pos][i] + g(m_dist, i, visitada & ~pos_visitada, m_sol);
        if (distancia < min)
        {
            min = distancia;
        }
    }
    m_sol[pos][visitada] = min;

    return min;
}

// recomponer_solucion -> Función que dada la matriz solución, realiza el recorrido inverso al realizado para 
// rellenar dicha matriz, con el fin de obtener el recorrido de ciudades a la cual corresponde la distancia mínima
// caculada en la función g()
list<int> recomponer_solucion(const vector<vector<double>> &m, int todas_visitadas, const vector<vector<double>> &L)
{
    list<int> res;
    res.push_back(0);
    // Añadimos la primera ciudad, e inicialmente tenemos todas las ciudades disponibles para elegir aquella
    // que nos ofrezca el camino más corto
    int disponibles = todas_visitadas;
    while (disponibles != 0)
    {
        double min = numeric_limits<double>::max();
        int pos_visitada;
        int pos;

        // Recorremos todas las ciudades menos la ciudad inicial
        for (int i = 1; i < m.size(); i++)
        {
            pos_visitada = (1 << (i - 1));

            // Evitamos las ciudades que no están disponibles ya que estas ya las hemos 
            // escogido anteriormente como  parte de la solución
            if ((disponibles & pos_visitada) == 0)
                continue;

            // Si ofrece un resultado mejor, guardamos la pos y dicho resultado
            if (L[res.back()][i] + m[i][disponibles & ~pos_visitada] < min)
            {
                min = L[res.back()][i] + m[i][disponibles & ~pos_visitada];
                pos = i;
            }
        }

        // 'Pos' es la ciudad que nos ofrece una ruta más corta, así que
        // la añadimos a la solución y deja de estar disponible
        pos_visitada = (1 << (pos - 1));
        disponibles = disponibles & ~pos_visitada;

        res.push_back(pos);
    }

    res.push_back(0);
    return res;
}

// tsp -> función que engloba los pasos para resolver el problema planteado: 1. Encontrar la distancia minima del
// recorrido y 2. Obtener dicho recorrido de ciudades
pair<double, list<int>> tsp(const vector<vector<double>> &L)
{
    pair<double, list<int>> solucion;

    int nsubsets = (1 << (L.size() - 1));
    int todas_visitadas = nsubsets - 1;

    // Creamos la matriz solucion, que será la que rellenaremos para obtener tanto el recorrido 
    // como la distancia minima de este. Dicha matriz tiene una dimensión de N(ciudades) * 2^N(conjuntos),
    // la cual, inicializaremos a -1.
    vector<vector<double>> m(L.size(), vector<double>(nsubsets, -1));
    for (int i = 0; i < L.size(); i++)
    {
        m[i][0] = L[i][0];
    }

    //Obtenemos la distancia mínima
    solucion.first = g(L, 0, todas_visitadas, m);
    //A raíz de la matriz solución recomponemos el recorrido 
    solucion.second = recomponer_solucion(m, todas_visitadas, L);

    return solucion;
}

int main(int argc, char *argv[])
{
    map<int, pair<double, double> > map; //un map con las posicion y las dimensiones.
    vector< vector<double> >  m_distancia; //cremaos un matriz con la distnacia entre dos pueblos
    double tama=0.0;
    
    string fp;
    if (argc<2) {
        cerr << "Formato " << argv[0] << " archivo.tsp" << endl;
        exit(EXIT_FAILURE);
    }

    fp = argv[1];

    // Se pasan las ciudades y sus dimensiones al map
    leer_puntos(fp,map);
    tama=map.size();
    m_distancia.resize(tama, vector<double>(tama,-1));

    // Creamos la matriz de distancias
    calcular_matriz(map,m_distancia);

    // vector<vector<double>> L = {{0.0, 3.0, 2.0, 3.0, 4.0},
    //                             {3.0, 0.0, 1.0, 3.0, 3.0},
    //                             {2.0, 1.0, 0.0, 3.0, 2.0},
    //                             {3.0, 3.0, 3.0, 0.0, 4.0},
    //                             {4.0, 3.0, 2.0, 4.0, 0.0}};
    
    // vector<vector<double>> J = {{0.0, 2.0, 1.0, 3.0, 4.0, 5.0, 5.0, 6.0},
    //                             {1.0, 0.0, 4.0, 4.0, 2.0, 5.0, 5.0, 6.0},
    //                             {5.0, 4.0, 0.0, 2.0, 2.0, 6.0, 5.0, 6.0},
    //                             {5.0, 2.0, 2.0, 0.0, 3.0, 2.0, 5.0, 6.0},
    //                             {4.0, 2.0, 4.0, 2.0, 0.0, 3.0, 5.0, 6.0},
    //                             {4.0, 2.0, 4.0, 2.0, 3.0, 0.0, 5.0, 6.0},
    //                             {4.0, 2.0, 4.0, 2.0, 4.0, 3.0, 0.0, 6.0},
    //                             {4.0, 2.0, 4.0, 2.0, 8.0, 3.0, 5.0, 0.0}};
    
    // vector<vector<double>> T = {{0.0, 3.0, 4.0, 2.0, 99.0, 3.0, 1.0, 1.0, 4.0, 4.0},
    //                             {3.0, 0.0, 3.0, 2.0, 99.0, 4.0, 4.0, 99.0, 1.0, 99.0},
    //                             {4.0, 3.0, 0.0, 2.0, 2.0, 99.0, 3.0, 2.0, 2.0, 3.0},
    //                             {2.0, 2.0, 2.0, 0.0, 2.0, 2.0, 99.0, 3.0, 3.0, 99.0},
    //                             {99.0, 99.0, 2.0, 2.0, 0.0, 1.0, 4.0, 1.0, 2.0, 2.0},
    //                             {3.0, 4.0, 99.0, 2.0, 1.0, 0.0, 3.0, 2.0, 3.0, 2.0},
    //                             {1.0, 4.0, 3.0, 99.0, 4.0, 3.0, 0.0, 3.0, 3.0, 3.0},
    //                             {1.0, 99.0, 2.0, 3.0, 1.0, 2.0, 3.0, 0.0, 99.0, 99.0},
    //                             {4.0, 1.0, 2.0, 3.0, 2.0, 3.0, 3.0, 99.0, 0.0, 1.0},
    //                             {4.0, 99.0, 3.0, 99.0, 2.0, 2.0, 3.0, 99.0, 1.0, 0.0}};

    // Ejecutamos nuestro algoritmo y calculamos el tiempo de ejecucion
    clock_t t_antes, t_despues;
    t_antes = clock();
    auto sol = tsp(m_distancia);
    t_despues = clock();

    // Mostramos la solución
    cout << "Coste mínimo: " << sol.first << endl;
    cout << "Solución: ";
    mostrar_solucion(sol.second);
    cout << endl << "Tiempo de ejecución: " << (double)(t_despues - t_antes) / CLOCKS_PER_SEC; 
    cout << endl;
}