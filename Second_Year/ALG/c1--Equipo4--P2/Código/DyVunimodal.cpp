#include <iostream>
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <chrono>

using namespace std;
using namespace std::chrono;

//generador de ejemplos para el problema de la serie unimodal de números. Se genera un índice aleatorio entre 1 y n-2, se asigna el mayor entero (n-1) a ese índice, a los índices anteriores a p se le asignan valores en orden creciente (0,1,...,p-1) y a los índices mayores que p se le asignan valores en orden decreciente (n-2, n-1,...,p

//compilar g++ -std=c++11 DyVunimodal.cpp -o DyVunimodal

double uniforme() //Genera un número uniformemente distribuido en el
                  //intervalo [0,1) a partir de uno de los generadores
                  //disponibles en C.
{
	double u;
	u = (double) rand();
	u = u/(double)(RAND_MAX+1.0);
	return u;
}

int posMax (const int * & v, int pos1, int pos2) {

	if (v[pos1] > v[pos2])
		return pos1;
	else
		return pos2;
}

int dyvunimodal(const int * v, int inicio, int fin) {

    	int tam = fin-inicio+1;
        int medio = (tam/2)+inicio;
        int a = v[medio-1];
        int b = v[medio+1];
        int vp = v[medio];

	assert(tam > 0);

	if (tam == 1) {  //Caso base 1. Solo tenemos 1 elemento
		return vp;
	}

	else if (tam == 2) {  //Caso base 2. Tenemos 2 elementos
		return v[posMax (v, inicio, fin)];
	}

	else {

		if(vp > a && vp > b) return vp; //Caso base 3. El pico es el medio

		else {

		    if(vp < b) {//El pico está a la derecha del medio
		        return dyvunimodal(v, medio + 1, fin);
		    }
		    if(vp > b) {//El pico está a la izquierda del medio
		        return dyvunimodal(v, inicio, medio);
		    }
		}
	}
}

int main(int argc, char * argv[])
{

	if (argc != 2)
	{
	cerr << "Formato " << argv[0] << " <num_elem>" << endl;
	return -1;
	}

	int n = atoi(argv[1]);

	if (n <= 0)
	{
	cerr << "num_elem > 0" << endl;
	return -1;
	}

	int pico;

	int * T = new int[n];
	assert(T);

	srand(time(0));
	double u=uniforme();
	int p=1+(int)((n-2)*u);
	T[p]=n-1;
	for (int i=0; i<p; i++) T[i]=i;
	for (int i=p+1; i<n; i++) T[i]=n-1-i+p;

	clock_t tantes,tdespues;
	double tiempo_transcurrido;
	const int NUM_VECES=10000;
	tantes=clock();
	for (int i=0; i<NUM_VECES;i++){
		pico = dyvunimodal(T, 0, n-1);
	}
	tdespues = clock();
	tiempo_transcurrido=((double)(tdespues-tantes)/((double)CLOCKS_PER_SEC* (double)NUM_VECES));

	cout << n << " " << tiempo_transcurrido << endl;

	delete [] T;

	return 0;
}
