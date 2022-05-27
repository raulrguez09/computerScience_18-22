/* Grupo C1-4:
    Antonio Lorenzo Gavilán Chacón
    Inés Nieto Sánchez
   	Raúl Rodríguez Pérez
	Francisco Javier Gallardo Molina

Asignatura Algoritmica (ALG)
Problemas tema 3: Voraz-Greedy
Version:0.1

EJERCICIO Asignacion de tareas
Supongamos que disponemos de n trabajadores y n
tareas. Sea cij > 0 el coste de asignarle el trabajo j al
trabajador i.
Una asignación de tareas puede ser expresada como
una asignación de los valores 0 ó 1 a las variables xij,
	xij = 0 significa que al trabajador i no le han asignado la tarea j,
	xij = 1 indica que sí.
Una asignación válida es aquella en la que a cada
trabajador sólo le corresponde una tarea y cada tarea
está asignada a un trabajador.
*/

#include <cstdlib>		// sdt::rand
#include <iostream>
#include <iomanip>      // std::setw
#include <vector>
#include <utility>

using namespace std;


//mostramos la matriz de costes
void mostrar (const vector< vector<int> > & m) {
    cout << endl <<"la matriz es:" << endl;
    cout<<setw(3);
    for(int i=0; i<m.size(); i++) {
        for(int j=0; j<m[i].size(); j++)
            cout<<m[i][j]<<setw(3);
        cout<<endl;
    }
}

//mostramos el vector de pares <trabajador,tarea>
void mostrar(const vector <pair<int,int> > & v) {
    cout << endl;
    for(int i=0; i<v.size(); i++) {
        cout<<"trabajador "<<v[i].first<<" tarea "<<v[i].second<<endl;
    }
    cout<<endl;
}

//creamos la matriz de costes de forma aleatoria
void crear ( vector< vector<int> > & m) {
    srand(time(NULL));
    for(int i=0; i<m.size(); i++) {
        for(int j=0; j<m[i].size(); j++)
            m[i][j]=(rand()%50)+1;//aleatorio entre 1-50
    }
}

//ponemos el valor de la fila y la columna a infinito
void modificarfilcol(int f,int c,vector< vector<int> > & m) {
    for(int i=0; i<m.size(); i++) {
        for(int j=0; j<m[i].size(); j++)
            if(i==f or j==c) m[i][j]=999;
    }
}

/* elegir en cada paso el par trabajador-
tarea con menor coste, de entre los compatibles
con las decisiones ya tomadas.
*/
vector <pair<int,int> > seleccionar(vector< vector<int> > & m) {
    vector <pair<int,int> > s;
    pair<int,int> obj;
    int aux;
    int valor=0;
    for(int contador=0; contador<m[0].size(); contador++) {
        obj.first=0;
        obj.second=0;
        aux=m[0][0];
        for(int i=0; i<m.size(); i++) {
            for(int j=0; j<m[i].size(); j++) {
                if( m[i][j]!=999 && m[i][j]<aux) {
                    aux=m[i][j];
                    obj.first=i;
                    obj.second=j;
                }
            }
        }
        s.push_back(obj);
        modificarfilcol(obj.first,obj.second,m);
        if(valor == 0){
          cout << "El trabajador " << obj.first << "tiene asignado el trabajo " << obj.second << endl;
          cout << "La matris con la fila y columna eliminada es esta: ";
          mostrar(m);
          valor=1;
        }
    }
    return s;
}

int main() {
    vector< vector<int> >  m;
    m.resize(4, vector<int>(4,-1));
    crear(m);
    mostrar(m);
    vector <pair<int,int> >  v;
    v=seleccionar(m);
    mostrar(v);
}
