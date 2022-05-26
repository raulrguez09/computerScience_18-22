#include <iostream>
using namespace std;

int main (){
	int multiplicador, multiplicando, resultado=0;
	cout << "INTRODUZCA UN ENTERO: ";
	cin >> multiplicador;
	cout << "INTRODUZCA OTRO ENTERO: ";
	cin >> multiplicando;
	cout << multiplicador << " x " << multiplicando << ": ";
	
	
	while (multiplicando!=1){
		if (multiplicando%2!=0){
		resultado=resultado+multiplicador;
		
	}
		multiplicador=multiplicador * 2;
		multiplicando=multiplicando/2;
	}
	
	cout << " = " << (resultado + multiplicador) << endl;
	system ("PAUSE");
	return 0;
	
}
