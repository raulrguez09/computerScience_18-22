/*Realizar un programa que lea n n�meros reales y muestre por pantalla el real le�do m�s cercano
al cero.*/

#include <iostream>
#include <stdlib.h>
#include <cmath>
using namespace std;

int main(){
	int i, n;
	double real, cercano;
	
	cout << "CUANTOS REALES QUIERE INTRODUCIR?: ";
	cin >> n;
	cout << "INTRODUZCA " << n << " REALES: " << endl;
	cin >> cercano;
	
	i=1;
	
	while (i<n){
	cin >> real;
	
	if (abs(real)>=0 && abs(real)<abs(cercano)){
	    cercano=real;
	    i++;
    }
    
    else 
    	i++;
	
}
	cout << "EL NUMERO MAS CERCANO AL CERO ES: " << cercano << endl;
	system ("PAUSE");
	return 0;
}
