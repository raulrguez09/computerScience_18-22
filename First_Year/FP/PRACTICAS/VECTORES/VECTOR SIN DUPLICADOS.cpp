#include <iostream>
using namespace std;

int main (){
	const int MAX=1000;
	int V[MAX], V_SR[MAX];
	int util_V, util_V_SR;
	bool encontrado;
	int j;
	
	do {
		cout << "INTRODUZCA No DE ELEMENTOS: ";
		cin >> util_V;
	}
	while (util_V < 0 || util_V > MAX);
	
	util_V_SR=0;
	
	for (int i=0;i<util_V;i++){
		cout << "\nINTRODUCIR ELEMENTO: ";
		cin >> V[i];
	}
	for (int i=0; i<util_V; i++){
		encontrado=false;
		j=0;
		while(j<util_V_SR && !encontrado){
			if (V[i]==V_SR[j])
			encontrado=true;
			
			else 
			j++;
		}
	if (!encontrado){
		V_SR[util_V_SR]=V[i];
		util_V_SR++;
	}
		
	}
	
	
	for (int i=0; i<util_V_SR;i++)
	cout << V_SR[i] << endl;
	
	system ("PAUSE");
	return 0;
}
