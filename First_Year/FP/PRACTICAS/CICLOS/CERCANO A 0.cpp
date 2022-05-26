/*Realizar un programa que lea n números reales y muestre por pantalla el real leído más cercano
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
