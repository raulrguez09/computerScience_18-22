#include <iostream>
using namespace std;

int main(){
	
	const int MAX=1000;
	char V[MAX], O[MAX];
	int util_V, util_O, k;
	bool encontrado;
	
	do{
		cout << "INTRODUZCA EL NUMERO DE ELEMENTOS A INTRODUCIR: ";
		cin >> util_V;
	}while(util_V < 0 && util_V > MAX);
	
	for (int i=0; i<util_V; i++){
		cout << "--> ";
		cin >> V[i];
	}
	
	util_O=0;
	
	for (int i=0; i<util_V; i++){
		encontrado=false;
		k=0;
		while (k<util_O && !encontrado){
			if (V[i]==O[k])
			encontrado=true;
			
			else k++;
		}
		
		if (!encontrado){
		O[util_O]=V[i];
		util_O++;
		}
		
		}
	cout << "\nELIMINANDO DUPLICADOS NOS QUEDA: ";
		
	for (int i=0; i<util_O; i++)
	cout << O[i] << " ";
	
	cout << endl;
	
	system("PAUSE");
	return 0;
	
	}
	

