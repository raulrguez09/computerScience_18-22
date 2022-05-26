#include <iostream>
#include <cmath>
using namespace std;

int main () {
	double a, b, c;
	
	cout << "\tSIENDO a^2 + b^2 = c^2 EL TRIPLE DE PITAGORAS" << endl;
	
	cout << "INTRODUZCA UN VALOR PARA a: ";
	cin >> a;
	
	cout << "\nINTRODUZCA UN VALOR PARA b: ";
	cin >> b;
	
	cout << "\nINTRODUZCA UN VALOR PARA c: ";
	cin >> c;
	
	if (pow(a,2) + pow(b,2) == pow(c,2)){
	    cout << "\nCON LOS VALORES INTRODUCIDOS, OBTENEMOS UN TRIPLE DE PITAGORAS" << endl;
		system("PAUSE");
		return 0;	
	}
	else {
		cout << "\nCON LOS VALORES INTRODUCIDOS, NO OBTENEMOS UN TRIPLE DE PITAGORAS" << endl;
		system ("PAUSE");
		return 0;
	}
}
