#include <iostream>

using namespace std;

int main(){
int entero;

cout << "INTRODUZCA UN NUMERO ENTERO: "; 
cin >> entero;

if (entero >0){
	cout << "\nEL NUMERO INTRODUCIDO ES POSITIVO" << endl;
	system ("PAUSE");
	return 0;
} 

else if (entero == 0){
	cout << "\nEL NUMERO INTRODUCIDO ES IGUAL A 0" << endl;
	system ("PAUSE");
	return 0;
}

else if (entero < 0){
	cout << "\nEL NUMERO INTRODUCIDO ES NEGATIVO" << endl;
	system ("PAUSE");
	return 0;
}
}
