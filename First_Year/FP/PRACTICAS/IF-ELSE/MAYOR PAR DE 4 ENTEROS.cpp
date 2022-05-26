#include <iostream>
#include <cmath>
using namespace std;

int main () {
int a,b,c,d;

cout << "INTRODUZCA UN VALOR ENTERO: ";
cin >> a;

cout << "\nINTRODUZCA UN SEGUNDO VALOR ENTERO: ";
cin >> b;

cout << "\nINTRODUZCA UN TERCER VALOR ENTERO: ";
cin >> c;

cout << "\nINTRODUZCA UN ULTIMO VALOR ENTERO: ";
cin >> d;

if (a != 0 && b != 0 && c != 0 && d != 0){
	if (a % 2 == 0 && a>b && a>c && a>d){
		cout << "\nEL MAYOR ENTERO PAR INTRODUCIDO ES: " << a << endl;
	}
	else if (b % 2 == 0 && b>a && b>c && b>d){
		cout << "\nEL MAYOR ENTERO PAR INTRODUCIDO ES: " << b << endl;
	}
	else if (c % 2 == 0 && c>b && c>a && c>d){
		cout << "\nEL MAYOR ENTERO PAR INTRODUCIDO ES: " << c << endl;
	}
	else if (d % 2 == 0 && d>b && d>c && d>a){
		cout << "\nEL MAYOR ENTERO PAR INTRODUCIDO ES: " << d << endl;
	}
	else if (a % 2 != 0 && b % 2 != 0 && c % 2 != 0 && d % 2 != 0){
		cout << "\nPOR FAVOR, REINICIE EL PROGRAMA E INTRODUZCA ALGUN VALOR PAR" << endl;
	}
	system ("PAUSE");
	return 0;
}
else {
	cout << "\nPOR FAVOR, REINICIE EL PROGRAMA Y NO INTRODUZCA NINGUN VALOR 0" << endl;
	system ("PAUSE");
	return 0;
}

}
