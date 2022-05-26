/** PRGRAMA PARA DETERMINAR SI UN VALOR ENTERO ES PAR O IMPAR **/

#include <iostream>
using namespace std;

int main (){
	int entero;
	bool es_par;
	
	cout << "INTRODUZCA UN NUMERO ENTERO: ";
	cin >> entero;
	
	if (entero % 2 == 0){
		es_par = true;
	}
	else {
		es_par = false;
	}
	
	if (es_par)
	cout << "\nEL ENTERO INTRODUCIDO ES PAR" << endl;
	else {
	 
	cout << "\nEL ENTERO INTRODUCIDO ES IMPAR" << endl;
    }
	system("PAUSE");
	
	return 0;
}
