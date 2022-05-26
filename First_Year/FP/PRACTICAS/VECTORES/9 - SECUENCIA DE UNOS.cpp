#include <iostream>
using namespace std;

int main(){
	const int MAX=1000;
	int V[MAX];
	int util_V;
	int contadormax=0;
	int posmax;
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
			if(V[k]==1){
			contador++;
			k++;
		}
			else seguir=false;
		}
		if (contador>contadormax){
			contadormax=contador;
			posmax=i;
		}
	}
	
	if (contadormax==0)
	cout << "NO SE HAN INTRODUCIDO CEROS" << endl;
	else 
	cout << "LA MAYOR SECUENCIA DE UNOS EMPIEZA EN LA POSICION " << posmax << " Y ES DE LONGITUD " << contadormax << endl;
	system("PAUSE");
	return 0;	
		
}
