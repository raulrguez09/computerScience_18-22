/* Programa que lea 25 enteros y muestre por pantalla los enteros que existen
entre el mayor de los negativos leídos y el menor de los positivos leídos */

#include <iostream>
using namespace std;

int main (){
	int i, p, introducido, positivo, negativo;
	
    cout << "INTRODUZCA 5 NUMEROS ENTEROS: ";
    positivo=2147483647;
    negativo=-2147483647 - 1;
    i=1;
    
    while (i<=5){
    	cout << "\n--> ";
    	cin >> introducido;
    	
    	if (introducido<0 && introducido>=negativo)
    		negativo=introducido;
    	if (introducido>0 && introducido<=positivo)
	        positivo=introducido;
    i++;			
	}
	
	//RELEEMOS LOS ENTEROS, PARA DETERMINAR LOS INTERNOS
	
	cout << "\nINTRODUZCA DE NUEVO LOS 5 NUMEROS ENTEROS: ";
	
	p=1;
	 while (p<=5){
    	cout << "\n--> ";
    	cin >> introducido;
    	
    	if (introducido==negativo)
    	cout << " (MAYOR NEGATIVO)";
    	
    	if (introducido==positivo)
    	cout << " (MENOR POSITIVO)";
    	
	    if (introducido>negativo && introducido<positivo)
	    cout << " (SE ENCUENTRA ENTRE LOS LÍMITES)";
	    
    p++;			
	}
	
	system ("PAUSE");
	return 0;
	
}
