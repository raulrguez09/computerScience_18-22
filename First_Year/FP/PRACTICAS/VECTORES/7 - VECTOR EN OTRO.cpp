#include <iostream>
using namespace std;

int main(){
	const int MAX=1000;
	int V[MAX], P[MAX];
	int util_V, util_P, pos;
	
	do{
		cout << "Introduzca el numero de elementos a introducir para el vector inicial: ";
		cin >> util_V;
	}while(util_V>MAX || util_V<=0);
	
	cout << "\nIntroduzca pues " << util_V << " elementos: " << endl;
	
	for (int i=0; i<util_V; i++)
		cin >> V[i];
		
	do{
		cout << "Introduzca el numero de elementos a introducir para el segundo vector: ";
		cin >> util_P;
	}while(util_P>MAX || util_P<=0);
	
	cout << "\nIntroduzca pues " << util_P << " elementos: " << endl;
	
	for (int i=0; i<util_P; i++)
		cin >> P[i];
	
	do{	
	cout << "EN QUE POSICION DEL PRIMER VECTOR QUIERE INTRODUCIR AL SEGUNDO?: ";
	cin >> pos;
}	while(pos<=0 || pos>util_V);

	int tmp=util_V;
	util_V=util_V+util_P;
	int contador=1;
	
	for (int k=util_V-1; k>=tmp;k--){
		V[k]=V[tmp-contador];
		contador++;
		}
		
	int h=0;
	for (int i=pos; h<util_P; i++){
		V[i]=P[h];
		h++;
		
	}
	cout << endl;
	
	for (int i=0; i<util_V; i++)
	cout << V[i] << " ";
		
}
