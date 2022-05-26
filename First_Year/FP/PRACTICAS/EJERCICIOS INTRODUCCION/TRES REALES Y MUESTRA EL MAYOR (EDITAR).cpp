/** PROGRAMA QUE LEYENDO TRES REALES,
MUESTRA POR PANTALLA EL MAYOR DE ELLOS **/

#include <iostream>
using namespace std;

int main (){ 
double real1, real2, real3;

cout << "INTRODUZCA UN VALOR REAL: ";
cin >> real1;

cout << "\nINTRODUZCA UN SEGUNDO VALOR REAL: ";
cin >> real2;

cout << "\nINTRODUZCA UN TERCER VALOR REAL: ";
cin >> real3;


if (real1>real2 && real1>real3){
	cout << "\nEL MAYOR DE LOS INTRODUCIDOS ES: " << real1 << endl;
	system("PAUSE");
	return 0;
}

else if (real2>real1 && real2>real3){
	cout << "\nEL MAYOR DE LOS INTRODUCIDOS ES: " << real2 << endl;
	system("PAUSE");
	return 0;
}

else if (real3>real2 && real3>real1){
	cout << "\nEL MAYOR DE LOS INTRODUCIDOS ES: " << real3 << endl;
	system("PAUSE");
	return 0;
}

else if (real3==real2 && real3==real1){
	cout << "\nLOS TRES REALES INTRODUCIDOS SON IGUALES" << endl;
	system("PAUSE");
	return 0;
}

else if (real3==real1 && real3>real2 && real1>real2){
	cout << "\nEL PRIMER Y EL TERCER REAL SON IGUALES, PERO MAYORES QUE EL SEGUNDO REAL. EL VALOR DE ESTOS ES: " << real1 << endl;
	system("PAUSE");
	return 0;
}

else if (real3==real2 && real3>real1 && real2>real1){
	cout << "\nEL SEGUNDO Y EL TERCER REAL SON IGUALES, PERO MAYORES QUE EL PPRIMER REAL. EL VALOR DE ESTOS ES:" << real2 << endl;
	system("PAUSE");
	return 0;
}

else if (real1==real2 && real1>real3 && real2>real3){
	cout << "\nEL PRIMER Y EL SEGUNDO REAL SON IGUALES, PERO MAYORES QUE EL TERCER REAL. EL VALOR DE ESTOS ES: " << real1 << endl;
	system("PAUSE");
	return 0;
}
}
