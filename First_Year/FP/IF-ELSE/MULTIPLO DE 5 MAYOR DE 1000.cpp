#include <iostream>

using namespace std;

int main(){
int entero;

cout << "INTRODUZCA UN NUMERO ENTERO: "; 
cin >> entero;

if (entero % 5 == 0 && entero > 1000){
	cout << "\nEL NUMERO INTRODUCIDO ES MULTIPLO DE 5 Y MAYOR QUE 1000" << endl;
	system ("PAUSE");
	return 0;
} 

else if (entero % 5 == 0 && entero < 1000){
	cout << "\nEL NUMERO INTRODUCIDO ES MULTIPLO DE 5 PERO MENOR QUE 1000" << endl;
	system ("PAUSE");
	return 0;
} 

else if (entero % 5 != 0 && entero > 1000){
	cout << "\nEL NUMERO INTRODUCIDO NO ES MULTIPLO DE 5 PERO SI MAYOR QUE 1000" << endl;
	system ("PAUSE");
	return 0;
} 
}
