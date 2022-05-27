#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <cmath>
#include <string>
#include <time.h>
#include <limits>
#include <sstream>
#include <list>
#include <map>

using namespace std;

//rellenamos la columna de -1 para que esta no se vuelva a utilizar.
void modificar_columna(vector< vector<double> > & m,int colum) {
    for(int i=0; i<m.size(); i++) {
        for(int j=0; j<m[i].size(); j++)
            if(colum==j) {
                m[i][j]=-1;
            }
    }
}
double recorrido(vector< vector<double> >  matriz) {
    vector<int>c;//ciudades selecionadas
    double d = 0.0;
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
    return d;
}

double cota_local = 0.0;
double cota_global = 0.0;
//numeric_limits<double>::max();;
int nodos_explorados = 0;

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

bool encuentraValor(int i, list<int> lista){
    list<int>::iterator it = lista.begin();
    bool encontrado = false;
    
    for(it; it != lista.end() && !encontrado; ++it){
        if(*it == i){
            encontrado = true;
        }
    }

    return encontrado;
}

void backtracking(int ciudad_actual, list<int> &visitadas, const vector< vector<double> > &matriz, double cota_real, double cota_opt, vector<double> &min_cota, list<int> &solucion_final)
{

    visitadas.push_back(ciudad_actual);
	nodos_explorados++; 
    int visita = 0;
    double distancia;

    if(visitadas.size() == matriz.size()){
        list<int>::iterator it = visitadas.begin();
        list<int>::iterator it_sig = it;
        ++it_sig;
        for(it; it_sig != visitadas.end(); ++it, ++it_sig){
            distancia += matriz[*it][*it_sig];
        }
        distancia += matriz[0][visitadas.back()];
        if(cota_global > distancia){
            cota_global = distancia;
            //cout << "COTA GLOBAL " << cota_global << endl;
            solucion_final = visitadas;
        }
    }
    else{
        cota_local = cota_real + cota_opt;
        if (cota_local < cota_global) {
            for (int i = 1; i < matriz.size(); i++){
                if(!encuentraValor(i, visitadas)){
                    double c_real = cota_real + matriz[ciudad_actual][i];
                    double c_opt = cota_opt - min_cota[ciudad_actual];

                    backtracking(i, visitadas, matriz, c_real, c_opt, min_cota, solucion_final);
                    visitadas.pop_back();
                }
            
            }
        }
    }
}

unsigned int factorial(unsigned int n){

    if (n == 0)
       return 1;

    return n * factorial(n - 1);
}

//devuelve las ciudades ordenadas con sus coordenadas.
void mostrar_resultado(const vector<int> &result,const map<int,pair<double,double> > &m) {
    for(int i=0; i<result.size(); i++) {
        pair<double,double> p;
        p=(m.find(result[i]+1))->second;
        cout<<result[i]+1<<" "<<p.first<<" "<<p.second<<endl;
    }
}

int main (int argc, char* argv[]) {	
	
	if(argc != 2){
		cerr << "USO: ./" << argv[0] << " archivo_ciudades.tsp" << endl;
		exit(1);
	}
    string fp;
    fp = argv[1];
	clock_t t_ini, t_fin;
	double secs;
    map<int, pair<double, double> >  m;//un map con las posicion y las dimensiones.
	vector< vector<double> > matriz_distancias; 
    
    fp = argv[1];
    // Se pasan las ciudades y sus dimensiones al map
    leer_puntos(fp,m);
    int tama = m.size();
    matriz_distancias.resize(tama, vector<double>(tama,0));
    calcular_matriz(m,matriz_distancias);

    //cota_global = recorrido(matriz_distancias);
    cota_global = numeric_limits<double>::max();
    //cout << "COTA GLOBAL " << cota_global << endl;
	
    list<int> visitadas, solucion_final;
    double cota_real = 0.0, cota_opt = 0.0;
    vector<double> min_cota;
    double minimo = numeric_limits<double>::max();
    
    for(int i = 0; i < matriz_distancias.size(); i++){
        for(int j = 0; j < matriz_distancias.size(); j++){
            if(i != j){
                if(matriz_distancias[i][j] < minimo){
                    minimo = matriz_distancias[i][j];
                }
            }
        }
        min_cota.push_back(minimo);
        minimo = numeric_limits<double>::max();
    }

    cout << endl;
    for(int i = 0; i < min_cota.size(); i++){
        cota_opt += min_cota[i];
    }
    
    t_ini = clock();
	backtracking (0, visitadas, matriz_distancias, cota_real, cota_opt, min_cota, solucion_final);
    t_fin = clock();

    solucion_final.push_back(0);
    vector<int> res;
    list<int>::iterator iter = solucion_final.begin();
    
    for(iter; iter != solucion_final.end(); ++iter){
        res.push_back(*iter);
    }

    // cout << endl << "res: ";
    // for(int i = 0; i < res.size(); i++){
    //     cout << res[i]+1 << " ";
    // }

    double distancia = 0;
	secs = (double)(t_fin - t_ini) / CLOCKS_PER_SEC;

    for(int i = 1; i < matriz_distancias.size(); i++){
	    distancia += matriz_distancias[res[i-1]][res[i]];
    }
    
    distancia += matriz_distancias[0][res[matriz_distancias.size() - 1]];

    cout << endl;
    cout << "Nodos explorados: " << nodos_explorados << endl << endl;
    cout << "Recorrido sol_final: "<< endl;
    mostrar_resultado(res, m);
    cout << endl << "Distancia: " << distancia << endl;
    cout << "Tiempo: " << secs << " seg" << endl;
}