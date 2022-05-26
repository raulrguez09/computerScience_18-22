

/** PROGRAMA PARA CALCULAR LA MEDIA ARITMÉTICA Y LA DESVIACIÓN TÍPICA
DE TRES VALORES REALES DADOS POR EL USURARIO **/

#include <iostream>
#include <cmath>

using namespace std;

int main (){
	
	double real1, real2, real3, media, desviacion;
	
	cout << "Introduzca el primer valor real: ";
	cin >> real1;	
	
	cout << "Introduzca el segundo valor real: ";
	cin >> real2;
	
	cout << "Introduzca el tercer valor real: ";
	cin >> real3;
	
	media = (real1 + real2 + real3)/3;
	
	desviacion = sqrt (((real1*real1 + real2*real2 + real3*real3 )/3) - media*media);
	
	cout << "El valor de la media aritmetica de " << real1 << ", " << real2 << " y " << real3 << " es: " << media << ". A su vez, la desviacion tipica sera: " << desviacion;
	
	return 0;
	
}
