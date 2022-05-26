/* Mostrar todos los números pares 
comprendidos entre dos variables enteras leídas por teclado. */

#include <iostream>
using namespace std;

int main () {
	int inferior, superior;
	int i;
	
	cout << "INTRODUZCA UN LIMITE INFERIOR: ";
	cin >> inferior;
	
	cout << "\nINTRODUZCA UN LIMITE SUPERIOR: ";
	cin >> superior;
	
    cout << "\nLOS PARES COMPRENDIDOS ENTRE [" << inferior << "," << superior << "] son:" << endl;
	
	i = inferior;
	
	while (i >= inferior  && i <= superior ){
		if ((i % 2 == 0)){
		cout << " --> " << i << endl;
		i= i +1;}
		else
		i= i + 1;
	}
	
    system ("PAUSE");
	return 0;
	
}
