#include <iostream>
using namespace std;

int main (){ 
int entero1, entero2, entero3;

cout << "INTRODUZCA UN VALOR ENTERO: ";
cin >> entero1;

cout << "\nINTRODUZCA UN SEGUNDO VALOR ENTERO: ";
cin >> entero2;

cout << "\nINTRODUZCA UN TERCER VALOR ENTERO: ";
cin >> entero3;


if (entero1>=entero2 && entero1>=entero3){
	if (entero2>=entero3){
		cout << entero3 << "    " << entero2 << "    " << entero1 << endl;
	}
	else {
		cout << entero2 << "    " << entero3 << "    " << entero1 << endl;
	}
	system("PAUSE");
	return 0;
}


else if (entero2>entero1 && entero2>entero3){
	if (entero1>=entero3){
		cout << entero3 << "    " << entero1 << "    " << entero2 << endl;
	}
	else {
		cout << entero1 << "    " << entero3 << "    " << entero2 << endl;
	}
	system("PAUSE");
	return 0;
}

else if (entero3>entero2 && entero3>entero1){
	if (entero2>=entero1){
		cout << entero1 << "    " << entero2 << "    " << entero3 << endl;
	}
	else {
		cout << entero2 << "    " << entero1 << "    " << entero3 << endl;
	}
	system("PAUSE");
	return 0;
}

}
