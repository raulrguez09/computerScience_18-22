#include <iostream>
using namespace std;

int main (){ 
int entero1, entero2, entero3, entero4;

cout << "INTRODUZCA UN VALOR ENTERO: ";
cin >> entero1;

cout << "\nINTRODUZCA UN SEGUNDO VALOR ENTERO: ";
cin >> entero2;

cout << "\nINTRODUZCA UN TERCER VALOR ENTERO: ";
cin >> entero3;

cout << "\nINTRODUZCA UN CUARTO VALOR ENTERO: ";
cin >> entero3;

if (entero1>=entero2 && entero1>=entero3 && entero1>=entero4 ){
	cout << "\nEL MAYOR DE LOS INTRODUCIDOS ES: " << entero1 << endl;
	system("PAUSE");
	return 0;
}

else if (entero2>=entero1 && entero2>=entero3 && entero2>= entero4){
	cout << "\nEL MAYOR DE LOS INTRODUCIDOS ES: " << entero2 << endl;
	system("PAUSE");
	return 0;
}

else if (entero3>=entero2 && entero3>=entero1 && entero3>=entero4){
	cout << "\nEL MAYOR DE LOS INTRODUCIDOS ES: " << entero3 << endl;
	system("PAUSE");
	return 0;
}
else if (entero4>=entero1 && entero4>=entero2 && entero4>=entero3){
	cout << "\nEL MAYOR DE LOS INTRODUCIDOS ES: " << entero4 << endl;
	system("PAUSE");
	return 0;
}
}
