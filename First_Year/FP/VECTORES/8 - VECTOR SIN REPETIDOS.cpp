#include <iostream>
using namespace std;

int main(){
	const int MAX=1000;
	char V[MAX];
	int util_V;
		
	do{
		cout << "Introduzca el numero de elementos a introducir: ";
		cin >> util_V;
	}while(util_V>MAX || util_V<=0);
	
	cout << "\nIntroduzca pues " << util_V << " elementos: " << endl;
	
	for (int i=0; i<util_V; i++)
		cin >> V[i];
		
	cout << "\nEl vector es el siguiente: ";
	
	for (int i=0; i<util_V;i++)
		cout << V[i] << " ";
		
	cout << endl <<  "\ny sin repetidos: ";
	
	bool comprobacion=true;
	
	for (int i=0; i<util_V;i++){
		for (int k=i+1; k<util_V; k++){
			if (V[k]==V[i]){
				for(int p=k; p<util_V;p++)
					V[p]=V[p+1];
				}
		}
		
		if(i==util_V-1 && comprobacion){
			i=0;
			comprobacion=false;
		}
	}
	int inicio;
	
	if (V[0]==V[1])
	inicio=1;
	else
	inicio=0;
	for (int i=inicio; i<util_V;i++)
	cout << V[i] << " ";

	
	cout << endl;
	
	system("PAUSE");
	return 0;
}
