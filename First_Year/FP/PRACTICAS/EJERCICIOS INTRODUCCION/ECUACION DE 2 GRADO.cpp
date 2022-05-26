/** PROGRAMA PARA CALCULAR lAS RAÍCES DE UNA ECUACIÓN DE SEGUNDO GRADO 
SEGÚN LOS VALORES DADOS A "A", "B" Y "C" POR EL USUARIO **/

#include <iostream>
#include <cmath>

using namespace std;

int main (){
	
	double x1, x2, A, B, C;
	double radical, denominador, interno;
	
	cout << "***** Siendo Ax^2 + Bx + C = 0 *****" << endl;

	cout << "\n Introduzca el valor de A: ";
	cin >> A;	
	
	cout << "\n Introduzca el valor de B: ";
	cin >> B;
	
	cout << "\n Introduzca el valor de C: ";
	cin >> C;
	
	if (A != 0) {
	  radical = sqrt(B*B - 4*A*C);
	  denominador = 2*A;
	  interno = B*B - 4*A*C;
		
	  x1 = (- B + radical)/ denominador ;
	
	  x2 = (- B - radical)/ denominador ;
	
	  if (interno < 0) {
	  	cout << "\nExisten dos raices, pero estas son complejas." << endl;
	  }
	  else {
	  	cout << "\nExisten dos raices, estas son: \n\t x1 = " << x1 << "    x2 = " << x2 << endl;
	  }
    }
    
    else {
    	x1 = -C/B;
    	cout << "\nLa unica raiz es: " << x1 << endl;
	}
	system ("PAUSE");	
	return 0;
	
}
