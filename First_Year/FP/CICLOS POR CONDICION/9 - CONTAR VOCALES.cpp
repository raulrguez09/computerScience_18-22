#include <iostream>
using namespace std;

int main (){
	
	string caracter;
	int n;
	
	cout << "INTRODUZCA CARACTERACTERES, CUANDO QUIERA PARAR INTRODUZCA 'ab': \n--> ";
	cin >> caracter;
	
	while (caracter != "ab"){
		if (caracter == "a" || caracter =="e" || caracter=="i" || caracter=="o" || caracter=="u")
		n++;

		cout << "--> ";
		cin >> caracter;
	}
	
	cout << "SE HAN INTRODUCIDO " << n << " VOCALES" << endl;
	
	system ("PAUSE");
	return 0;
	
}
