#include <iostream>
using namespace std;

int main (){
	int n, k, L;  // Introducimos 3 enteros, n=contador de fila, k=n�mero a introducir en cada fila, L=n� filas pir�mide.
	
	do {
		cout << "Introduzca el numero de filas a visualizar: ";
		cin >> L;
	}
	while (L<=0);  // Aplicamos un filtro para que siga preguntando cuando se introduzca un n�mero de filas igual o menor a 0.
	
	cout << endl;
	
	k=L;
	
	do {
		k=k%10;
	}
	while(k>=10);  //Aplicamos otro filtro para que en la pir�mide s�lo veamos d�gitos entre 0-9.
	
	for (n=L; n>=0; n--){  // �ste ser� el for que har� que vayamos bajando de filas.
		for (int i=0; i<L-n; i++) // �ste ser� el for que har� que vayamos introduciendo los correspondientes espacios, para que visualicemos una pir�mide.
			cout << " ";
			
		for (int i=(2*n-1); i>0; i--){ // �ste ser� el for que introduzca los d�gitos (k) en cada fila de la pir�mide.
			cout << k;	
		}
		
		if (k==0) // Introducimos un condicional, para que cuando el digito sea 0, el siguiente en introducirse sea 9.
			k=9;
			
		else // Si no se cumple, simplemente disminuir� una unidad.
			k--;

		cout << endl;
	}
	
	system ("PAUSE");
	
	return 0;
	
}
