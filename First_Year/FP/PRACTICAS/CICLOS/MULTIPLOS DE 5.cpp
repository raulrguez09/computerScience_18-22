/* Programa que muestra por pantalla 
los 1000 primeros múltiplos de 5. */

#include <iostream>
using namespace std;

int main () {
	int multiplo, entero;
	int i;
	
	cout << "LOS 1000 PRIMEROS MULITPLOS DE 5 SON: ";
	
	i = 0;
	entero = 5;

	
	while (i<=1000 ){
		multiplo = entero * i;
		cout << " --> " << multiplo << endl;
		i++;

	}
	
    system ("PAUSE");
	return 0;
	
}
