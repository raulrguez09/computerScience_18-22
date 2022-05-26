/*Determinar si n términos de entrada están ordenados de forma creciente. */

#include<iostream>
using namespace std;

int main (){
	
	int i, n, termino, anterior;
	bool condicion=true;
	cout << "CUANTOS TERMINOS DESEA INTRODUCIR?: ";
	cin >> n;
	
	cout << "\nINTRODUZCA " << n << " TERMINOS: \n--> ";
	cin >> anterior;
	
	i=1;
	
	while (i<n){
		cout << "\n--> ";
		cin >> termino;
		
		if (termino>=anterior && condicion){
	     	i++;
		    anterior=termino;
	     	condicion=true;
	}
		else {
		condicion=false;
		i++;
		}
	}
    
    if (condicion){
        cout << "\nLOS NUMEROS ESTAN ORDENADOS DE FORMA ASCENDENTE" << endl;
        system ("PAUSE");
	    return 0;
	}
	else {
		cout << "\nLOS NUMEROS NO ESTAN ORDENADOS DE FORMA ASCENDENTE" << endl;
        system ("PAUSE");
	    return 0;
	} 
}
