#include<iostream>
using namespace std;

int main(){
	const int MAX=1000;
	int util_V;
	int V[MAX];
	
	do{
		cout << "INTRODUZCA EL NUMERO DE ELEMENTOS A INTRODUCIR: ";
		cin >> util_V;
	}while(util_V <= 0 || util_V>MAX);
	
	cout << "\nINTRODUZCA PUES " << util_V << " ELEMENTOS: " << endl;
	
	for(int i=0; i<util_V; i++)
		cin >> V[i];
	
	int max=util_V;
	bool va_bien=true;
	for(int i=0; i<max && va_bien; i++)
		for (int j=i+1; j<max-1 && va_bien; j++){
			if (V[j]>V[i]){
				i++;
				va_bien=true;
			}
			else if (V[j]<=V[i] && V[j]<=V[0]){
				i++;
				va_bien=true;
				}
				else
				va_bien=false;				
			
		}
	for (int i=0; i<util_V; i++)
	cout << V[i] << " ";
			
	if (va_bien && V[util_V-1]<=V[0])
	cout << "\nEL VECTOR ESTA ORDENADO DE FORMA CICLICA" << endl;
	else 
	cout << "\nEL VECTOR NO ESTA ORDENADO DE FORMA CICLICA" << endl;
	
	system ("PAUSE");
	return 0;
}
