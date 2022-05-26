/* leer 3 valores enteros y decir si están ordenados ascendente,
descendente ó desordenados */

#include <iostream>

using namespace std;

enum TIPO {ascendente, descendente, desordenado, iguales};

int main () {
	int en1, en2, en3;
	TIPO t;
	cout << "INTRODUZCA UN NUMERO ENTERO: ";
	cin >> en1;
	
	cout << "\nINTRODUZCA UN SEGUNDO NUMERO ENTERO: ";
	cin >> en2;
	
	cout << "\nINTRODUZCA UN TERCER NUMERO ENTERO: ";
	cin >> en3;
	
	if (en1 < en2){
		if (en2 < en3){
		t = ascendente;	
		}
		else 
		t= desordenado;
	}
	else if (en1 > en2){
		if (en2 > en3)
		t = descendente;
		else 
		t = desordenado;
	}
	else if (en1 == en2 && en2 == en3)
	    t = iguales;
	    
	if (t==ascendente)
	cout << "\nLOS NUMEROS HAN SIDO INTRODUCIDOS EN UN ORDEN ASCENDENTE " << en1 << " < " << en2 << " < " << en3 <<endl;
	
	else if( t==descendente)
	cout << "\nLOS NUMEROS HAN SIDO INTRODUCIDOS EN UN ORDEN DESCENDENTE " << en1 << " > " << en2 << " > " << en3 <<endl;
    
    else if (t==iguales)
    cout << "\nLOS NUMEROS INTRODUCIDOS SON IGUALES " << en1 << " = " << en2 << " = " << en3 <<endl;
    
    else if (t==desordenado)
    cout << "\nLOS NUMEROS INTRODUCIDOS ESTAN DESORDENADOS " << en1 << " " << en2 << " " << en3 <<endl;

    system ("PAUSE");
    return 0;
}


