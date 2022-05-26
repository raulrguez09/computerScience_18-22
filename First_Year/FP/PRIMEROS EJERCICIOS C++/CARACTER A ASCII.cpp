/** Programa que lee un letra y muestra por pantalla su código ASCII.
También muestra su mayúscula correspondiente **/ 

#include <iostream>

using namespace std;

int main (){
	char a, mayus;
	double x, y;
	
	cout << "Pulse cualquier caracter del teclado para saber su valor ASCII: ";
	cin >> a;
	
	x = a;
	mayus = x - 32;
	y = mayus;
	
	cout << "\nEl codigo es: " << x << endl;
	
	cout << "\nSu mayuscula correspondiente es: " << mayus << " y su valor ASCII es : " << y;
	
	return 0;
}




