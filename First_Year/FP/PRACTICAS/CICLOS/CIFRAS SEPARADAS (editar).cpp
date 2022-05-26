/* Realizar un programa que muestre separadas las cifras de un entero de entrada */

#include <iostream>
using namespace std;

int main (){
	int i, n, cifra;
	
	cout << "INTRODUZCA UN NUMERO ENTERO: ";
	cin >> n;
	
	i=1;
	while (i<=2){
	    cifra=(n%100)/(10*i);
    	cout << "\t" << cifra;
    	i++;
    }
}
