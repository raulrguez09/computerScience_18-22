#include <iostream>
using namespace std;

int main(){
	
	const int MAX=1000;
	char V[MAX], V2[MAX], UNION[MAX], INTER[MAX];
	int util_V, util_V2, util_UNION, util_INTER, k;
	bool encontrado;
	
	do{
		cout << "INTRODUZCA EL NUMERO DE ELEMENTOS A INTRODUCIR EN EL PRIMER VECTOR: ";
		cin >> util_V;
	}while(util_V < 0 && util_V > MAX);
	
	for (int i=0; i<util_V; i++){
		cout << "--> ";
		cin >> V[i];
	}
	
	do{
		cout << "INTRODUZCA EL NUMERO DE ELEMENTOS A INTRODUCIR EN EL SEGUNDO VECTOR: ";
		cin >> util_V2;
	}while(util_V2 < 0 && util_V2 > MAX);
	
	for (int i=0; i<util_V2; i++){
		cout << "--> ";
		cin >> V2[i];
	}
	
	util_INTER=0;
	util_UNION=0;
	
	for (int i=0; i<util_V; i++){
		encontrado=false;
		k=0;
		while (k<util_V2 && !encontrado){
			if (V[i]==V2[k])
			encontrado=true;
			
			else k++;
		}
		
		if (!encontrado){
		UNION[util_UNION]=V[i];
		util_UNION++;
		}
		else{
		INTER[util_INTER]=V[i];
		UNION[util_UNION]=V[i];
		util_INTER++;
		util_UNION++;
		}
		}
	for (int i=0; i<util_V2; i++){
		encontrado=false;
		k=0;
		while (k<util_V && !encontrado){
			if (V2[i]==V[k])
			encontrado=true;
			
			else k++;
		}
		
		if (!encontrado){
		UNION[util_UNION]=V2[i];
		util_UNION++;
		}
		
	}
	
	cout << "\nEL VECTOR UNION ES: ";
		
	for (int i=0; i<util_UNION; i++)
	cout << UNION[i] << " ";
	
	cout << "\nEL VECTOR INTERSECCION ES: ";
		
	for (int i=0; i<util_INTER; i++)
	cout << INTER[i] << " ";
	
	cout << endl;
	
	system("PAUSE");
	return 0;
	
	}
	

