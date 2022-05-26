#include <iostream>
using namespace std;

int main(){
	const int MAX=1000;
	char V[MAX];
	int util_V;
	int contadormax=0;
	int posmax;
	char letramax;
	
	do{
		cout << "Introduzca el numero de elementos a introducir: ";
		cin >> util_V;
	}while(util_V>MAX || util_V<=0);
	
	cout << "\nIntroduzca pues " << util_V << " elementos: " << endl;
	
	for (int i=0; i<util_V; i++)
		cin >> V[i];
		
	for (int i=0; i<util_V;i++){
		int k=i;
		int contador=0;
		bool seguir=true;
		while(k<=util_V && seguir){
			if(V[k]==V[i]){
			contador++;
			k++;
		}
			else k++;
		}
		if (contador>contadormax){
			contadormax=contador;
			letramax=V[i];
		}
	}
	
	 
	cout << "EL CARACTER MAS REPETIDO ES " << letramax << ", " << contadormax << " VECES" << endl;
	system("PAUSE");
	return 0;	
		
}
