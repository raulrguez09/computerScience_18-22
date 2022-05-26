/* Escribir un programa para determinar si un número entero es un cuadrado perfecto. Recordar
que estos números son de la forma n2, es decir, los números 1, 4, 9, 16, … Para ello, no se puede
hacer uso de la función sqrt, sino que tendremos que ir calculando los cuadrados de los
números desde el 1 en adelante. */

#include <iostream>
using namespace std;

int main (){
	int i, n;
	bool perfecto=false;
	cout << "INTRODUZCA UN NUMERO ENTERO: ";
	cin >> n;
	
	for (i=1; i<=n; i++)
	if (i*i==n)
	perfecto=true;
	
	if (perfecto)
	cout << "EL NUMERO " << n << " ES PERFECTO" << endl;
	else 
	cout << "EL NUMERO " << n << " NO ES PERFECTO" << endl;
	
	system ("PAUSE");
	return 0;
}
