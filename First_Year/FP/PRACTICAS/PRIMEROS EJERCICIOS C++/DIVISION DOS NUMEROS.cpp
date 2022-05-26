// PROGRAMA QUE LEE DOS NUMEROS Y REALIZA SU DIVISION

#include <iostream>
using namespace std;

int main ()
{
	double numero1, numero2, division;
	
	cout << "Introduzca numero 1: ";
	cin >> numero1;
	
	cout << "Introduzca numero 2: ";
	cin >> numero2;
	
	if (numero2 == 0) {
		cout << "No es posible realizar la operacion" << endl;
   }
   
   else {
	division = numero1 / numero2;
	
	cout << "El resultado es: " <<division;
	return 0;
   }
}
