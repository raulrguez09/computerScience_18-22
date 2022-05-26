/* Realizar un programa que lea 20 letras ('a' … 'z') y determine si el número de veces que ha
aparecido 'a' es mayor al numero de veces de 'z'. Considerar que puede darse la circunstancia
de que alguno de ellos, o ambos, no aparezcan. */

#include <iostream>
using namespace std;

int main (){
	int i=0, contadora=0, contadorz=0;
	char letra;
	cout << "INTRODUZCA 20 LETRAS: " << endl;
	while (i<20){
		cin >> letra;
		if (letra=='a'){
		   contadora++;
	       i++;
	    }
		else if (letra=='z'){
		   contadorz++;
		   i++;}
		   else
		   i++;
	}
	if (contadora>contadorz)
	cout << "'a' HA APARECIDO MAS VECES QUE 'z'" << contadora << ">" << contadorz << endl;
	else if (contadorz>contadora)
		cout << "'z' HA APARECIDO MAS VECES QUE 'a'" << contadorz << ">" << contadora << endl;
		else if(contadora==contadorz)
				cout << "'a' HA APARECIDO LAS MISMAS VECES QUE 'z'" << endl << "\t\t" << contadorz << "=" << contadora << endl;

	system ("PAUSE");
	return 0;
}
