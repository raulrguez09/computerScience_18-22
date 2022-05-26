/* Desarrollar un programa para mostrar los divisores propios de n. */

#include <iostream>

using namespace std;

int main (){
	
	int i, n;
	
	cout << "INTRODUZCA UN NUMERO ENTERO POSITIVO PARA CONOCER SUS DIVISORES: ";
	cin >> n;
	
	i=1;
	
	 while (i<=n){
		if (n%i==0){
			cout << "\n--> " << i;
			i++;
		}
		else i++;
	}

}
