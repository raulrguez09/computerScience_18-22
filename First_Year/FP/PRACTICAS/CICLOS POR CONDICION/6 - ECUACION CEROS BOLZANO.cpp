#include <iostream>
#include <stdlib.h>
#include <cmath>
using namespace std;

int main (){
	double negativo=0, positivo=1, precision, intervalo, pto_medio, sustitucion;
	
	bool seguir=true;
	
	cout << "	**	x^3 + x - 1 = 0	 **" << endl;
	
	cout << "\nINTRODUZCA EL NIVEL DE PRECISION DESEADO: ";
	cin >> precision;
	
	pto_medio = (negativo+positivo)/2;
	
	sustitucion= pow(pto_medio,3) + pto_medio - 1.0;
	
	intervalo = abs(negativo-positivo);
	
	while (intervalo>precision && seguir){
	
		if (sustitucion < 0){
			negativo = pto_medio;
		}

		else if (sustitucion > 0){
			positivo = pto_medio;
		
		}
			else 
			seguir=false;	
	
	}
	
	cout << "SEGUN EL TEOREMA DE LOS CEROS DE BOLZANO, EL PUNTO MAS CERCANO AL 0 DE LA ECUACIÓN ENTRE [0,1] ES " << pto_medio << endl;
	
	system ("PAUSE");
	return 0;
	
}
