/** PROGRAMA PARA INTERCAMBIAR EL VALOR 
DE TRES VARIABLES ENTRE SÍ **/


#include <iostream>
#include <cmath>
using namespace std;

int main () {
	double x, y, z, aux; // Declaramos una variable auxiliar 
	
	x = 10;
	y = 20;   // DEFINIMOS LOS VALORES DE LAS VARIABLES
	z = 30;
	  
    cout << "** INTERCAMBIO DE VARIABLES **" << endl;
    cout << "\nEN PRINCIPIO x: " << x << " y: " << y << " y z: " << z << endl;
	aux = y;
	y = x;    // REALIZAMOS LOS CAMBIOS PEDIDOS
	x = z;    // EN UN ORDEN DETERMINADO
	z = aux;
	
    cout << "\nAHORA LOS VALORES SE HAN INTERCAMBIADO" << endl;
	cout << "\nx:  " << x << endl;
	cout << "\ny:  " << y << endl;
	cout << "\nz:  " << z << endl;
	return 0;
}
