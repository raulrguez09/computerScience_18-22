/** Realizar un programa que lea dos complejos y muestre por pantalla el que tiene mayor módulo.
El módulo de un número complejo a+bi es la raíz cuadrada de la suma de los cuadrados de a y
b. **/

#include <iostream>
#include <cmath>

using namespace std;

int main(){
	double a, b, a2, b2;
	
	cout << "SIENDO a + bi UN NUMERO COMPLEJO,..." << endl;
	
	cout << "INTRODUZCA UN VALOR REAL PARA a: ";
	cin >> a;
	
	cout << "\nINTRODUZCA UN VALOR REAL PARA b: ";
	cin >> b;
	
	cout << "\nSIENDO a' + b'i OTRO NUMERO COMPLEJO,..." << endl;
	
	cout << "INTRODUZCA UN VALOR REAL PARA a': ";
	cin >> a2;
	
	cout << "\nINTRODUZCA UN VALOR REAL PARA b': ";
	cin >> b2;
		
	if (sqrt(pow(a,2) + pow(b,2)) >= sqrt(pow(a2,2) + pow(b2,2))){
		cout << "\nEL MAYOR COMPLEJO ES: " << a << " + " << b << "i" << endl;
		system ("PAUSE");
		return 0;
	}
	
	else {
	    cout << "\nEL MAYOR COMPLEJO ES: " << a2 << " + " << b2 << "i" << endl;
	    system ("PAUSE");
		return 0;
	}
	
	
}
