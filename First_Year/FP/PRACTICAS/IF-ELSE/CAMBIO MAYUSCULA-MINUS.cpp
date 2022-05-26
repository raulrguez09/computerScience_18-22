#include <iostream>

using namespace std;

int main (){
	char letra, cambio ;
	int ascii;
	
	cout << "Pulse cualquier letra del teclado: ";
	cin >> letra;
	
	ascii = letra;
	
	if ((ascii >= 65 && ascii <= 90) || (ascii >= 97 && ascii <= 122)){
		if (ascii>=65 && ascii <=90){
			ascii = letra + 32;
			cambio = ascii;
			cout << "\n\tDADA UNA LETRA MAYUSCULA, SU MINUSCULA ES: " << cambio << endl;
		}
		
		else {
			ascii = letra - 32;
			cambio = ascii;
			cout << "\n\tDADA UNA LETRA MINUSCULA, SU MAYUSCULA ES: " << cambio << endl;
		}
		
		system ("PAUSE");
		return 0;

	}
	
	else {
		cout << "\n\tREINICIE EL PROGRAMA E INTRODUZCA UNA LETRA" << endl;
		system ("PAUSE");
		return 0;
	}
}
