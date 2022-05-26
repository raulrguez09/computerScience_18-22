/** DADO UN NUMERO ENTERO DE 3 DÍGITOS (O MENOS), EL PROGRAMA LOS MUESTRA
POR SEPARADO **/

#include <iostream>
using namespace std;

int main (){
	int entero;
	
	cout <<"INTRODUZCA UN NUMERO ENTERO DE TRES DIGITOS: ";
	cin >> entero;
	if (entero>999){
		
		cout << "\nEL NUMERO INTRODUCIDO SUPERA LOS TRES DIGITOS, REINICIE EL PROGRAMA E INTRODUZCA OTRO" << endl;
		return 0;
	}
	
	cout << " " << entero/100 << "   " << (entero % 100)/10 << "   " << (entero % 100)%10 << endl;
	system("PAUSE");
	return (0);

}
