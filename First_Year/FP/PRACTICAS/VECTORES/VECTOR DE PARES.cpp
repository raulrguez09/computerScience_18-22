#include <iostream>
using namespace std;

int main (){
	const int MAX=1000;
	int V[MAX], V_pares[MAX];
	int util_V, util_V_pares;
	
	do {
		cout << "INTRODUZCA No DE ELEMENTOS: ";
		cin >> util_V;
	}
	while (util_V < 0 || util_V > MAX);
	
	util_V_pares=0;
	
	for (int i=0;i<util_V;i++){
		cout << "\nINTRODUCIR ELEMENTO: ";
		cin >> V[i];
	}
	for (int i=0; i<util_V; i++){
		if (V[i]%2==0){
			V_pares[util_V_pares]=V[i];
			util_V_pares++;
		}
	}
	
	for (int i=0; i<util_V_pares;i++)
	cout << V_pares[i] << endl;
	
	system ("PAUSE");
	return 0;
}
