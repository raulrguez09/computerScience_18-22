/** PROGRAMA PARA RESOLVER UN SISTEMA DE ECUACIONES
INTRODUCIENDO EL VALOR DE LOS COEFICIENTES Y TERMINOS INDEPENDIENTES **/


#include <iostream>
#include <cmath>

using namespace std;

int main (){
	
	double x, y, A, B, C, D, E, F;
	cout << "*** SIENDO (Ax + By = C) Y (Dx + Ey = F) UN SISTEMA DE ECUACIONES ***" << endl;
	
	cout << "\nINTRODUZCA UN VALOR PARA A: ";
	cin >> A;
	
	cout << "\nINTRODUZCA UN VALOR PARA B: ";
	cin >> B;
	
	cout << "\nINTRODUZCA UN VALOR PARA C: ";
	cin >> C;
	
	cout << "\nINTRODUZCA UN VALOR PARA D: ";
	cin >> D;
	
	cout << "\nINTRODUZCA UN VALOR PARA E: ";
	cin >> E;
	
	cout << "\nINTRODUZCA UN VALOR PARA F: ";
	cin >> F;
	
	y = (F - (D*C)/A)/(E + (-D*B)/A);
	
	x = (C - B*y)/A;
	
	cout << "\nx= " << x << endl;
	cout << "\ny= " << y << endl;
	
	return 0;
	
	
}
