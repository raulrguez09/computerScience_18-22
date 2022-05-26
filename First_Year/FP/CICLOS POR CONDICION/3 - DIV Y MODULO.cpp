/* Dados dos enteros a y b determinar a/b y a%b sin usar las operaciones “/” y “%”. (con un ciclo
while). */

#include <iostream>
using namespace std;

int main (){
	int a, b, div, mod, resto;
	
	cout << "INTRODUZCA UN VALOR a: ";
	cin >> a;
	
	cout << "\nINTRODUZCA UN VALOR b: ";
	cin >> b;
	
	resto= a-b;
	div = 0;
	while (resto >= 0){
		resto = resto - b;
		div++;
	}
   
if (resto<0)
    resto = resto + b;

	cout << "\na/b: " << div << endl << "\na%b: " << resto << endl;
	
	system ("PAUSE");
	return 0;
	
	
}
