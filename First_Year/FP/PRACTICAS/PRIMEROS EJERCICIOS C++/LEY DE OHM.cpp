

/** PROGRAMA PARA CALCULAR EL VOLTAJE, SEGÚN LA LEY DE OHM,
MEDIANTE LA INTENSIDAD Y RESISTENCIA DADA POR EL USUARIO **/

#include <iostream>
#include <cmath>

using namespace std;

int main (){
	
	double voltaje, intensidad, resistencia;
	
	cout << "Introduzca el valor de la intensidad: ";
	cin >> intensidad;	
	
	cout << "Introduzca el valor de la resistencia: ";
	cin >> resistencia;
	
	voltaje = intensidad * resistencia;
	
	cout << "Siendo la intensidad de " << intensidad << " A" " y la resistencia de " << resistencia << " Ohm, el valor del voltaje es de: " << voltaje << "V";
	
	return 0;
	
}
