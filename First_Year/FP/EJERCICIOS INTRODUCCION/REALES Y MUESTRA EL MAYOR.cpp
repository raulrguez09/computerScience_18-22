/** PROGRAMA QUE LEYENDO DOS REALES,
MUESTRA POR PANTALLA EL MAYOR DE ELLOS **/

#include <iostream>
using namespace std;

int main (){ 
double real1, real2;

cout << "INTRODUZCA UN VALOR REAL: ";
cin >> real1;

cout << "\nINTRODUZCA UN SEGUNDO VALOR REAL: ";
cin >> real2;

if (real1<real2){
	cout << "\nEL MAYOR DE LOS INTRODUCIDOS ES: " << real2 << endl;
	return 0;
}
else if (real2<real1){
	cout << "\nEL MAYOR DE LOS INTRODUCIDOS ES: " << real1 << endl;
	return 0;
}
else if (real1==real2){
	cout << "\nAMBOS REALES SON IGUALES" << endl;
	return 0;
}
}
