/* La Sucesi�n de Fibonacci es la siguiente sucesi�n infinita de n�meros naturales: 1, 1, 2, 3, 5, 8,
13, 21, 34, 55, 89,144, 233, 377 �. Esta sucesi�n se inicia con 1 y 1, y a partir de ah� cada
elemento, es la suma de los dos anteriores. Escribir un programa que muestre el t�rmino
en�simo de la Sucesi�n de Fibonacci. */

#include <iostream>
using namespace std;

int main (){
	int numero, i, n, anterior;
	
	cout << "QUE NUMERO DE LA SUCESION DE FIBONACCI QUIERE CONOCER?: ";
	cin >> n;
	
	i=2;
	numero=1;
	anterior=0;
	while (i<=n){
		numero=anterior+numero;
		anterior=numero-anterior;
		i++;
	}
	cout << "EL NUMERO " << n << " DE LA SUCESION DE FIBONACCI ES: " << numero << endl;
	system ("PAUSE");
	return 0;
	
	
}
