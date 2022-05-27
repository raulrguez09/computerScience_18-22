#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <limits>

using namespace std;

/*
Grupo C1-4
Miembros: Raúl Rodríguez Pérez, Antonio Lorenzo Gavilán Chacón,
          Inés Nieto Sánchez, Francisco Javier Gallardo Molina
Asignatura: Algoritmica (ALG)
Practica 5: Algoritmos de Vuelta Atrás(Backtracking) y de Ramificación y Poda(Branch and Bound)
Version:0.1

Ejercicio: Resolución del problema del Transporte de Mercancías

*/
double cota_local = 0.0;
double cota_global = numeric_limits<double>::max();
int nodos = 0;

//Backtraking recorre nuestro grafo en profundidad asegurándose con el vector distribuidos que no se ha distribuido a un punto de ventas y siendo venta_actual
//el nodo a analizar
void backtracking(int nivel, int venta_actual, vector<bool> &distribuidos, int solucion[], const vector<vector<double>> matriz, double cota_local, int solucion_final[]){

	solucion[nivel-1] = venta_actual;
	distribuidos[venta_actual] = true;
	nodos++;	//Contamos los nodos explorados

	//Recorremos todos los puntos de venta
	for(int venta = 0; venta < distribuidos.size(); venta++){
		//Si todavía no se ha distribuido a ese punto de venta lo analizamos
		if(distribuidos[venta] == false){
			//Establecemos cota local
			cota_local += matriz[nivel][venta];

			if(cota_local < cota_global){
				//Evaluamos a los hijos descendiendo en profundidad
				backtracking(nivel+1,venta,distribuidos,solucion, matriz, cota_local, solucion_final);
			}
			//Si no estamos en un nodo hoja(todavia no hemos llegado a la solucion) deshacemos los cambios hechos
			if(!(nivel == (distribuidos.size()-1))){
				cota_local = cota_local - matriz[nivel][venta];
			}
			else{
				//Si hemos llegado a nodo hoja (solucion), si la cota local es mejor que la global guardamos la solución
				if(cota_local < cota_global){
					cota_global = cota_local;
					for(int i = 0; i < distribuidos.size(); i++){
						solucion_final[i] = solucion[i];
					}
				}
			}
			distribuidos[venta] = false;
		}
	}
}

//Dada una solución para el problema CalculaDistancia hace la suma de las distancias del punto de distribución al de ventas
double CalculaDistancia(vector<bool>distribuidos,vector<vector<double>> matriz_distancias, int solucion_final[]){
	double distancia_total = 0;

	for(int i = 0; i < distribuidos.size(); i++){
    	distancia_total += matriz_distancias[i][solucion_final[i]];
    }

	return distancia_total;
}

//Función para obtener las distribuciones que dan la suma mínima de las distancias entre los puntos de venta y los puntos de distribución
double getDistribucionMinima(const vector<vector<double>> matriz_distancias, vector<int> &sol, int &nodos_explorados){
    const int TAM = matriz_distancias.size();
    double distancia_total = 10000000;

    //Calculamos y nos quedamos con la menor distancia, partiendo desde distintos puntos de venta
    for(int i = 0; i < TAM; i++){
		vector<bool> distribuidos(TAM,false);	//Vector para indicarnos si ya se ha distribuido a un punto de venta
		int solucion[TAM];
		int solucion_final[TAM];

    	cota_local += matriz_distancias[0][i];	//Guardamos en cota local la distancia al primer punto de venta
    	backtracking(1,i,distribuidos,solucion,matriz_distancias, cota_local, solucion_final);
    	double distancia = CalculaDistancia(distribuidos,matriz_distancias,solucion_final);

		//Nos quedamos con la distancia más pequeña de los puntos de venta
    	if(distancia < distancia_total){
    		distancia_total = distancia;
    		nodos_explorados = nodos;
    		for(int i = 0; i < TAM; i++){
    			sol.push_back(solucion_final[i]);
    		}
    	}
    	nodos = 0;
    	cota_local = 0.0;
    	cota_global = 10000000000000;
    }

    return distancia_total;
}


int main(int argc, char *argv[]){

	//Inicialización de las matrices

	// vector<vector<double>>  L = {{30, 14, 28, 28, 32, 7, 12, 27, 9, 19, 17, 22, 13, 18},
	// 														{34, 32, 22, 25, 5, 21, 12, 8, 4, 28, 5, 14, 4, 3},
	// 														{35, 7, 18, 30, 22, 10, 22, 18, 17, 35, 10, 27, 18, 27},
	// 														{14, 32, 10, 12, 29, 33, 2, 34, 18, 3, 6, 23, 32, 12},
	// 														{2, 7, 16, 2, 8, 34, 32, 30, 9, 19, 13, 27, 18, 24},
	// 														{19, 1, 15, 33, 33, 25, 10, 26, 23, 12, 24, 5, 15, 31},
	// 														{29, 11, 8, 32, 12, 24, 34, 21, 23, 30, 15, 33, 14, 29},
	// 														{24, 32, 17, 7, 34, 33, 5, 31, 23, 15, 22, 10, 28, 11},
	// 														{16, 8, 6, 9, 20, 14, 6, 32, 3, 4, 17, 27, 35, 33},
	// 														{24, 13, 26, 13, 10, 8, 21, 8, 5, 26, 4, 28, 5, 26},
	// 														{2, 34, 1, 18, 6, 8, 28, 26, 23, 34, 23, 27, 3, 4},
	// 														{18, 2, 2, 7, 16, 29, 20, 27, 1, 5, 35, 7, 32, 4},
	// 														{35, 1, 31, 2, 0, 33, 21, 6, 5, 14, 32, 29, 12, 19},
	// 														{20, 16, 24, 3, 19, 27, 10, 35, 20, 31, 26, 22, 1, 26}};


	// vector<vector<double>>  C = {{30, 14, 28, 28, 32, 7, 12, 27, 9, 19, 17, 22},
	// 															{13, 18, 34, 32, 22, 25, 5, 21, 7, 8, 4, 28},
	// 															{5, 14, 4, 3, 35, 7, 18, 30, 22, 10, 22, 18},
	// 															{17, 35, 10, 27, 18, 27, 14, 32, 10, 12, 29, 33},
	// 															{2, 34, 18, 3, 6, 23, 32, 12, 2, 9, 16, 2},
	// 															{8, 34, 23, 30, 9, 19, 13, 27, 18, 24, 19, 1},
	// 															{15, 33, 33, 25, 10, 26, 23, 12, 24, 5, 15, 31},
	// 															{29, 11, 8, 32, 12, 24, 34, 21, 23, 30, 15, 33},
	// 															{14, 29, 24, 32, 17, 7, 34, 33, 5, 31, 23, 15},
	// 															{22, 10, 28, 11, 16, 8, 6, 9, 20, 14, 6, 32},
	// 															{3, 4, 17, 27, 35, 33, 24, 13, 26, 13, 10, 8},
	// 															{21, 8, 5, 26, 4, 28, 5, 26, 2, 34, 1, 18}};

	// vector<vector<double>>  Y = {{34, 16, 32, 32, 37, 8, 13, 31, 11, 22},
	// 															{19, 25, 14, 21, 39, 37, 26, 29, 5, 24},
	// 															{1, 9, 5, 32, 6, 16, 5, 4, 40, 8},
	// 															{21, 34, 25, 12, 26, 21, 20, 39, 11, 31},
	// 															{21, 31, 16, 36, 11, 14, 33, 37, 2, 38},
	// 															{21, 3, 7, 27, 36, 14, 2, 5, 18, 2},
	// 															{9, 39, 36, 34, 10, 22, 15, 31, 21, 27},
	// 															{21, 1, 17, 38, 28, 29, 11, 30, 26, 14},
	// 															{28, 6, 18, 36, 33, 13, 9, 26, 14, 28},
	// 															{19, 24, 26, 5, 18, 27, 16, 33, 28, 2}};

	// vector<vector<double>> 	T = {{13, 6, 35, 9, 5, 12, 22, 17},
	// 															{2, 5, 32, 12, 5, 17, 9, 15},
	// 														{10, 23, 14, 14, 3, 16, 23, 5},
	// 														{7, 8, 21, 26, 13, 15, 8, 32},
	// 														{9, 10, 11, 6, 4, 6, 2, 3, 8},
	// 														{3, 6, 12, 54, 34, 1, 23, 22},
	// 														{9, 35, 21, 27, 12, 13, 5, 8},
	// 														{25, 16, 2, 14, 15, 1, 34, 9}};

	// vector<vector<double>> 	U = 	{{9.0, 10.0, 11.0, 50.0, 20.0},
  //                           		{10.0, 11.0, 14.0, 15.0, 16.0},
  //                           		{11.0, 14.0, 16.0, 17.0, 18.0},
  //                         			{50.0, 15.0, 17.0, 18.0, 19.0},
  //                         			{20.0, 16.0, 18.0, 19.0, 50.0}};

	// vector<vector<double>> 	M = 	{{9.0, 14.0, 12.0, 90.0, 30.0},
  //                               {61.0, 4.0, 14.0, 15.0, 13.0},
  //                              	{14.0, 14.0, 16.0, 112.0, 18.0},
  //                              	{500.0, 54.0, 217.0, 18.0, 9.0},
  //                              	{400.0, 6.0, 218.0, 19.0, 40.0}};

    vector<vector<double>> matriz_distancias = 	{{20, 500, 100, 40, 50},
                                				{500, 30, 10, 15, 60},
                               					{100,10 , 35, 200, 11},
                               					{40, 15, 200, 80, 70},
                               					{50, 60, 11, 70, 55}};

		clock_t tantes;
		clock_t tdespues;

   	int TAM = matriz_distancias.size();
   	int nodos_explorados = 0;
    vector<int> sol;	//En sol almacenamos la solución final

		tantes = clock();
    double distancia_total = getDistribucionMinima(matriz_distancias, sol, nodos_explorados);
		tdespues = clock();

		// cout << TAM << " " << ((double)(tdespues-tantes))/CLOCKS_PER_SEC << endl;

		//Muestra por pantalla del resultado
    cout << "NODOS EXPLORADOS: " << nodos_explorados << endl;
    cout << "DISTANCIA TOTAL: " << distancia_total << endl << endl;

    for(int i = 0; i < TAM; i++){
    	cout << "Punto de distribución: " << i << " ---> " << "Punto de venta: " << sol[i] << endl;
    }

    return 0;
}
