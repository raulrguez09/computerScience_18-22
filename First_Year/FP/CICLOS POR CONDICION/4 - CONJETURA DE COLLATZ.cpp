#include <iostream>
using namespace std;

int main (){
	bool es_par;
	int entero;
	
	cout << "\t\t\"Si n es par, se divide entre 2, \n\t\tsi no lo es, se multiplica por 3 y suma 1.\"" << endl;
	cout << "\nIntroduza un numero entero: ";
	cin >> entero;
	
	while (entero!=1){
		if (entero%2==0)
			entero=entero/2;			
		
		else
		entero=(entero*3) + 1;
	}
	
	cout << "GRACIAS A LA CONJETURA DE COLLATZ LLEGAMOS AL " << entero << endl;
	
	system("PAUSE");
	return 0;
	
}
