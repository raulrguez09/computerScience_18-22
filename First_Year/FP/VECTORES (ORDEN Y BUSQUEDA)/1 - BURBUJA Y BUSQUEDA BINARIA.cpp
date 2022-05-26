#include<iostream>
using namespace std;

int main(){
	const int MAX=1000;
	int util_V, tmp;
	int V[MAX];
	
	do{
		cout << "INTRODUZCA EL NUMERO DE ELEMENTOS A INTRODUCIR: ";
		cin >> util_V;
	}while(util_V <= 0 || util_V>MAX);
	
	cout << "\nINTRODUZCA PUES " << util_V << " ELEMENTOS: " << endl;
	
	for(int i=0; i<util_V; i++)
		cin >> V[i];
		
	for (int izda = 0; izda < util_V; izda++){
		for (int i = util_V-1 ; i > izda ; i--){
			if (V[i] < V[i-1]){
				tmp = V[i];
				V[i] = V[i-1];
				V[i-1] = tmp;
			}
		}
	}
	
	cout << endl << "EL VECTOR ORDENADO ES: ";
	for (int i=0; i<util_V; i++)
		cout << V[i] << " ";
	cout << endl;
	
	int buscado;
	
	cout << "INTRODUZCA UN ELEMENTO A BUSCAR EN EL VECTOR: ";
	cin >> buscado;
	
	int izda = 0;
	int dcha = util_V - 1;
	bool encontrado = false;
	int pos_encontrado;
	int centro;
	
	while (izda <= dcha && !encontrado){
		centro = (izda + dcha) / 2;
			if (V[centro] == buscado)
				encontrado = true;
			else if (buscado < V[centro])
					dcha = centro - 1;
				else
					izda = centro + 1;
	}
	if (encontrado)
		pos_encontrado = centro;
	else
		pos_encontrado = -1;
		
	if (encontrado)
	cout << "EL ELEMENTO SE HA ENCONTRADO EN LA POSICION " << pos_encontrado << endl;
	else
	cout << "EL ELEMENTO NO SE HA ENCONTRADO EN EL VECTOR" << endl;
	
	system ("PAUSE");
	return 0;
}
