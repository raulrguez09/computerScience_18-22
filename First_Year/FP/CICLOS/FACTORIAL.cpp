/* Programa que pida por pantalla un numero y devuelva el factorial de n */

#include <iostream>

using namespace std;

int main () {
	int n, i;
	long long int factorial;
	cout << "INTRODUZCA UN VALOR PARA HALLAR SU FACTORIAL: ";
	cin >> n;
	
	i=1;
	factorial=1;
	while (i <= n){
		factorial = factorial * i;
		i++;
	}
	
	cout << "\nEL FACTORIAL DE " << n << " ES: " << factorial << endl;
	system ("PAUSE");
	return 0;
	
}
