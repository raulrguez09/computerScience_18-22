

/** PROGRAMA PARA CALCULAR LOS VALORES DE x 
SEGÚN LOS VALORES DADOS A "A", "B" Y "C" POR EL USUARIO **/

#include <iostream>
#include <cmath>

using namespace std;

int main (){
	
	double x1, x2, A, B, C;
	
	cout << "***** Siendo Ax^2 + Bx + C = 0 *****" << endl;

	cout << "\n Introduzca el valor de A: ";
	cin >> A;	
	
	cout << "\n Introduzca el valor de B: ";
	cin >> B;
	
	cout << "\n Introduzca el valor de C: ";
	cin >> C;
	
	x1 = (- B + sqrt(B*B - 4*A*C))/ (2*A) ;
	x2 = (- B - sqrt(B*B - 4*A*C))/ (2*A) ;
	
	cout << "\n x1: " << x1 << endl; 
	cout << "\n x2: " << x2;	
	return 0;
	
}
