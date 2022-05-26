/* Realizar un programa que lea enteros hasta que se introduzca un elemento par y muestre por
pantalla la media de los datos leídos (el par no debe contar para calcular la media). */

#include <iostream>
using namespace std;

int main (){
	
	int n, suma, i;
	int media;
	
	cout << "INTRODUZCA VALORES PARA REALIZAR SU MEDIA, SI DESEA PARAR, INTRODUZCA UN PAR: \n-->";
	cin >> n;
	
	suma = 0;
	media = 0;
	for (i=0; (n%2)!= 0; i++){
		suma = suma + n;
		cout << "\n-->";
		cin >> n;
	}
	
	media = suma / i ;
	
	cout << "\nLA MEDIA DE LOS IMPARES INTRODUCIDOS ES: " << media << endl;
	
	system ("PAUSE");
	return 0;
}	
	
