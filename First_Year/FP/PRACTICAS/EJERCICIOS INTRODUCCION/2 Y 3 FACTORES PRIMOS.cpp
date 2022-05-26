/** PRGRAMA PARA DETERMINAR SI UN VALOR ENTERO TIENE DE FACTORES PRIMOS AL 2 Y AL 3 **/

#include <iostream>
using namespace std;

int main (){
	int entero;
	bool factor;
	
	cout << "INTRODUZCA UN NUMERO ENTERO: ";
	cin >> entero;
	
	if (entero % 2 == 0 && entero % 3 == 0){
		factor = true;
	}
	else {
		factor = false;
	}
	
	if (factor)
	cout << "\nLOS FACTORES PRIMOS DEL VALOR INTRODUCIDO, " << entero << ", INCLUYEN AL 2 Y AL 3" << endl;
	else 
	cout << "\nEL 2 Y EL 3 NO SON FACTORES PRIMOS DEL VALOR INTRODUCIDO, " << entero << endl;
	
	system("PAUSE");
	
	return 0;
	
}
