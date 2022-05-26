/** Programa que lee un número real, y escribe la parte entera descartando la parte
decimal **/

#include <iostream>

using namespace std;

int main (){
	int entera;
	
	cout << "Introduzca un numero real para visualizar su parte entera: ";
	cin >> entera;
	
	if (entera < 0){
		
	    cout << "\nLa parte entera es: " << entera - 1;
	    
	    return 0; 
	}
	
    cout << "\nLa parte entera es: " << entera;

    return 0;
}
	
	
