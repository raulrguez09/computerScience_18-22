/* Grupo C1-4:
    Antonio Lorenzo Gavilán Chacón
    Inés Nieto Sánchez
   	Raúl Rodríguez Pérez
	Francisco Javier Gallardo Molina

Asignatura Algoritmica (ALG)
practica 5: Branch and Bound
Version:0.1

EJERCICIO Comerciante de comercio (TSP) Estrategias Branch and Bound
Dado un conjunto de ciudades y una matriz con las distancias entre todas ellas, un viajante debe recorrer
todas las ciudades exactamente una vez, regresando al punto de partida, de forma tal que la distancia
recorrida sea mínima.
Mas formalmente, dado un grafo G, conexo y ponderado, se trata de hallar el ciclo hamiltoniano de mínimo
peso de ese grafo.
Para emplear un algoritmo de ramificación y poda es necesario utilizar una cota inferior: un valor menor o
igual que el verdadero coste de la mejor solución (la de menor coste) que se puede obtener a partir de la
solución parcial en la que nos encontremos.
Para realizar la poda, guardamos en todo momento en una variable C el costo de la mejor solución obtenida
hasta ahora (que se utiliza como cota superior global: la solución óptima debe tener un coste menor a esta
cota). Esa variable puede inicializarse con el costo de la solución obtenida utilizando un algoritmo voraz
(como los utilizados en la practica 2). Si para una solución parcial, su cota inferior es mayor o igual que la
cota global (superior) entonces se puede realizar la poda.
Como criterio para seleccionar el siguiente nodo que hay que expandir del árbol de búsqueda (la solución
parcial que tratamos de expandir), se emplear el criterio LC o "más prometedor".
En este caso consideraremos como nodo m�s prometedor aquel que presente el menor valor de cota
inferior.
Para ello se debe de utilizar una cola con prioridad que almacene los nodos ya generados (nodos vivos).
*/

//compilar: g++ TSPBranchBound.cpp -o TSPBranchBound
//ejecutar: ./TSPBranchBound archivo.tsp

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
#include <queue>          // std::priority_queue
#include <list>          // std::list
#include <limits>
using namespace std;

//-------------------------------------------------- funciones -----------------------------------------------

bool ExisteFichero (const string &nombre)
{
    ifstream fichero;
    bool problema;
    fichero.open (nombre.c_str());
    problema = fichero.fail();
    if (!problema) fichero.close();
    return ((problema) ? false : true);
}

string EliminarEspacios (const string & str) {
    size_t first = str.find_first_not_of(' ');

    if (string::npos == first){
        return str;
    }

    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

void leer_puntos(string &nombre, map<int, pair<double, double> > &M) {
    ifstream datos;
    pair<double,double> p;
    int ciudad;
    bool parar = false;
    string linea;

    if (!ExisteFichero(nombre)) {
        cerr << "\nError: no puedo abrir " << nombre << "\n\n";
        exit (1);
    }

    datos.open(nombre.c_str());

    if (!datos) {
        cerr << "Error: no puedo abrir " << nombre << endl;
        exit (3);
    }

    // Buscamos la sección donde empiezan los nodos
    while (datos && !parar) {
        getline (datos, linea);
        parar = (linea == "NODE_COORD_SECTION");
    }

    parar = false;

    while (datos && !parar) {
        getline (datos, linea);
        linea = EliminarEspacios (linea);

        // Si termina la sección paramos
        if (linea == "EOF") {
            parar = true;
        }

        else {
            stringstream iss (linea);
            iss >> ciudad >> p.first >> p.second;
            M[ciudad] = p;
        }
    }

    datos.close();
}


//mostrar matriz
void mostrar (const vector< vector<double> > & m) {
    cout<<"la matriz de distancias es:"<<endl << endl;
    //cout<<setw(3);
    for(int i=0; i<m.size(); i++) {
        //cout<<"Ciudad "<<i+1<<": "<<endl;
        for(int j=0; j<m[i].size(); j++)
            cout << setprecision (5) <<m[i][j]<< "\t";
        cout<<endl;
        cout<<endl;
    }
}
//mostrar vector
void mostrar (const vector<int> & m) {
    cout<<"el vector  es:"<<endl;
    for(int i=0; i<m.size(); i++) {
        cout<<m[i]<<"  ";
    }
    cout<<endl;
}
//calcular distancia
double euclides (double xi,double yi,double xj,double yj) {
    double aux1=(xj-xi)*(xj-xi);
    double aux2=(yj-yi)*(yj-yi);
    aux2=aux1+aux2;
    double aux=sqrt(aux2);
    return aux;

}
//creamos la matriz de distancias
//Asignamos a la distnacia entre la misma ciudad como -1.
void calcular_matriz(map<int, pair<double, double> >  m,vector< vector<double> > & matriz) {
    for(int i=0; i<matriz.size(); i++) {
        for(int j=0; j<matriz[i].size(); j++)
            if(i!=j) {
                matriz[i][j]=euclides(m[i+1].first,m[i+1].second,m[j+1].first,m[j+1].second);
            }

    }
}
//rellenamos la columna de -1 para que esta no se vuelva a utilizar.
void modificar_columna(vector< vector<double> > & m,int colum) {
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
vector<int> recorrido(vector< vector<double> >  matriz,double & d) {
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
    //a�adirle la distnacia del ultimo nodo al inicio
    d+=matriz[nodo][0];
    //no le a�adimos de nuevo el nodo 1..
    //c.push_back(1);
    return c;
}

//devuelve las ciudades ordenadas con sus coordenadas.
//a�ade la ciduad 1
void mostrar_resultado(const vector<int> &result,const map<int,pair<double,double> > &m) {
    for(int i=0; i<result.size(); i++) {
        pair<double,double> p;
        p=(m.find(result[i]))->second;
        cout<<result[i]<<" "<<p.first<<" "<<p.second<<endl;
    }
    pair<double,double> p;
    p=(m.find(1))->second;
    cout<<1<<" "<<p.first<<" "<<p.second<<endl;
}
vector<double> calcularMenorArista(const vector< vector<double> > & m) {
    vector<double> salida(m.size());
    int min=0,j;
    for(int i=0; i<m.size(); i++) {
        min=m[i][0];
        j=1;
        if(min==-1) {
            min=m[i][1];
            j++;
        }
        for(; j<m[i].size(); j++) {
            if(m[i][j]<min && m[i][j]!=-1)	min=m[i][j];
        }
        salida[i]=min;
    }
    return salida;
}


double distanciaCiudades(int c1,int c2,const vector< vector<double> > & m) { //restar uno ya que la ciduad n, en la matriz es la n-1
    return m[c1-1][c2-1];

}
//--------------------------------------------------class Solucion------------------------------------------------
class Solucion {
public:
    //constructor
    Solucion(int tama) {
        pos_e=distancia=estimador=0;
        x.push_back(1);//le pasamos la ciduad 1
        ciudadesRestantes.assign(tama-1,0);//-1 ya que la ciudad 1 no se la metemos
        crearCiudades();
    }
    //creamos la lista de ciudades
    void crearCiudades() {
        int i=2;//empezamos en la ciudada 2 ya que el un lo metemos inicialmente.
        for (list<int>::iterator it=ciudadesRestantes.begin(); it !=ciudadesRestantes.end(); ++it) {
            *it=i;
            i++;
        }
    }
    //calcula la cota por greedy
    void greedy(const vector< vector<double> >  & matriz) {
        x=recorrido(matriz,distancia);
        ciudadesRestantes.clear();

    }
    double getDistancia() {
        return distancia;
    }
    //calcula la cota a partirdel vectro de arista menores
    void calcularCotaLocal(const vector<double> & arista_menor) { //en arista_menor en la posicion 0, tenemos la ciudad 1.
        estimador=distancia;
        for (list<int>::iterator it=ciudadesRestantes.begin(); it !=ciudadesRestantes.end(); ++it) {
            estimador+=arista_menor[(*it)-1];//creo que es -1
        }
        //podemos tambn a�adirle siempre la arista de la ciudad 1, ya que tenemos que volver, ->estimador mas preciso
        estimador+=arista_menor[0];
    }
    double CotaLocal() const {
        return estimador;
    }
    bool EsSolucion(int tama) {
        return x.size()==tama;
    }

    //devuelve en un vector el resto de ciudades
    vector<int> resto_ciudades() {
        vector<int> aux;
        for (list<int>::iterator it=ciudadesRestantes.begin(); it !=ciudadesRestantes.end(); ++it) {
            aux.push_back(*it);
        }
        return aux;
    }
    //a�adade una ciudad al vectro y sus distnacia
    void anadirciudad(int a,const vector< vector<double> >  &m) {
        //Le volvemos a restar uno ya que la ciduad n, en la matriz es la n-1
        distancia+=distanciaCiudades(x.back(),a,m);//a�ade la distancia para ir a la ciudad
        x.push_back(a);
    }
    //quita una ciudad del vector y si distnacia
    void quitarciudad(const vector< vector<double> > & m) {
        //le quitamos a la ultima ciduad la que habia
        //Le volvemos a restar uno ya que la ciduad n, en la matriz es la n-1
        distancia-=distanciaCiudades(x[x.size()-2],x.back(),m);//quita la distancia para ir a la ciudad
        x.pop_back();//quitamos la ultima ciudad a�adida
    }

    void quitarcidudadRestante(int a) {
        for (list<int>::iterator it=ciudadesRestantes.begin(); it !=ciudadesRestantes.end(); ++it) {
            if(*it==a) {
                ciudadesRestantes.erase(it);
                break;
            }
        }
    }
    void anadircidudadRestante(int a) {
        ciudadesRestantes.push_back(a);

    }
    //calcula distancia
    double Evalua(const vector< vector<double> > & m) { //devuelve la distnacia y añade la distancia para ir a la ciudad 1.
        distancia+=distanciaCiudades(x.back(),1,m);
        return distancia;
    }
    bool operator<( const Solucion & s) const { //ordenados de menos a mayor
        return estimador > s.estimador;
    }

    void mostrar() {
        cout<<" las ciudades son:"<<endl;
        for(int i=0; i<x.size(); i++) cout<<x[i]<<"   ";
        cout<<x[0]<<endl;
        cout<<"la distancia es: "<<distancia<<endl;
    }
    vector<int> devolverSolucion() {
        return x;
    }
private:
    vector<int> x; // Almacenamos la solucion
    int pos_e; // Posicion de la ultima decision en X
    double distancia;
    double estimador; // Valor del estimador para el nodo X
    list<int> ciudadesRestantes;
};
//--------------------------------------------------class Solucion------------------------------------------------
//////////////////////////////////////////////////////////////
Solucion Branch_and_Bound(const vector< vector<double> > & matriz,const vector<double> & arista_menor,int tama)
{
    vector<int> aux;
    priority_queue<Solucion> Q;
    Solucion n_e(tama), mejor_solucion(tama) ; //nodoe en expansion
    mejor_solucion.greedy(matriz);//calculamos la cota pro greedy
    //double CG=mejor_solucion.getDistancia(); // Cota Global
    double CG = numeric_limits<double>::max();
    //cout << endl << endl << "Distancia Greedy: " << CG << endl << endl;
    double distancia_actual=0;
    Q.push(n_e);
    int tamanio_cola_nodos_vivos = Q.size();
    int tamanio_max_cola_nodos_vivos = tamanio_cola_nodos_vivos;
    int nodos_expandidos = 0;
    int numero_podas = 0;
    while ( !Q.empty() && (Q.top().CotaLocal() < CG) ) {
        n_e = Q.top();
        Q.pop();
        nodos_expandidos += 1;
        aux=n_e.resto_ciudades();
        for(int i=0; i<aux.size(); i++) {
            n_e.anadirciudad(aux[i],matriz);//a�adimos ciudad y le sumamos distancia
            n_e.quitarcidudadRestante(aux[i]);//quietamos la ciudad de ciudadrestante
            if ( n_e.EsSolucion(tama) ) {
                distancia_actual = n_e.Evalua(matriz);
                if (distancia_actual < CG) {
                    CG = distancia_actual;
                    mejor_solucion = n_e;
                }
            }
            else {
                n_e.calcularCotaLocal(arista_menor);
                if (n_e.CotaLocal()<CG ) {
                    Q.push( n_e );
                }
                else
                    numero_podas += 1;
            }
            n_e.quitarciudad(matriz);//la ultima que se ha a�adido
            n_e.anadircidudadRestante(aux[i]);//a�adimos la ultma que se quito
        }
        tamanio_cola_nodos_vivos = Q.size();
        if (tamanio_cola_nodos_vivos > tamanio_max_cola_nodos_vivos) {
            tamanio_max_cola_nodos_vivos = tamanio_cola_nodos_vivos;
        }
    }
    cout << endl;
    cout << "Numero de nodos expandidos: " << nodos_expandidos << endl;
    cout << "Tamanio maximo de la cola con prioridad de nodos vivos: " << tamanio_max_cola_nodos_vivos << endl;
    cout << "Numero de podas realizadas: " << numero_podas << endl << endl;
    return mejor_solucion;
}

////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char * argv[])
{
    map<int, pair<double, double> >  m;//un map con las posicion y las dimensiones.
    vector< vector<double> >  matriz;//cremaos un matriz con la distnacia entre dos pueblos
    vector<int> ciu;//vector
    vector<double> menor_arista;
    int tama=0;
    double distancia = 0.0;
    clock_t tantes;    // Valor del reloj antes de la ejecución
    clock_t tdespues;  // Valor del reloj despu�s de la ejecución
    //--------------------------------------------------------------------
    //calcualr matriz, menor_arista y m.
    string fp;

    if (argc<2) {
        cerr << "Formato " << argv[0] << " archivo.tsp" << endl;
        exit(EXIT_FAILURE);
    }

    fp = argv[1];
    // Se pasan las ciudades y sus dimensiones al map
    leer_puntos(fp,m);
    tama=m.size();
    matriz.resize(tama, vector<double>(tama,-1));

    calcular_matriz(m,matriz);
    menor_arista=calcularMenorArista(matriz);

    //------------------------------------------------------------------------

    tantes = clock();
    Solucion s=Branch_and_Bound(matriz,menor_arista,tama);
    tdespues = clock();

    //s.mostrar();
    mostrar(matriz);
    ciu=s.devolverSolucion();
    distancia=s.getDistancia();
    mostrar_resultado(ciu,m);//añade la ciduad 1

    cout<< endl << "distancia: "<<distancia<<endl;

    cout << endl;
    cout << "Tiempo empleado: " << ((double)(tdespues-tantes))/CLOCKS_PER_SEC << " seg" << endl << endl;

    return 0;
}