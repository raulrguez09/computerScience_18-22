/* Programa para determinar si un entero positivo n es primo */

#include <iostream>
using namespace std;

int main (){
	int n, i;
	bool ESPRIMO=true;
	cout << "INTRODUZCA UN ENTERO POSITIVO: ";
	cin >> n;
	
	if (n<=0){
		cout << "\nREINICIE EL PROGRAMA E INTRODUZCA UN ENTERO POSITIVO" << endl;
		system("PAUSE");
		return 0;
	}
	else {
		i=2;
		while (ESPRIMO && i<n){
			if (n%i==0){
				ESPRIMO=false;
			}
			else {
				i++;
			}
			}
			if (ESPRIMO)
			cout << "\nEL NUMERO " << n << " ES PRIMO" << endl;

			else 
			cout << "\nEL NUMERO " << n << " NO ES PRIMO" << endl;
			
			system("PAUSE");
			return 0;
		   
		}
	}

