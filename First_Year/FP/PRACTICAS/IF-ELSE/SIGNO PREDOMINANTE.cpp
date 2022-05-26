#include <iostream>

using namespace std;

int main (){
	
	int entero1, entero2, entero3;
	
	cout << "INTRODUZCA UN ENTERO CON SU SIGNO: ";
	cin >> entero1;
	
	cout << "\nINTRODUZCA UN SEGUNDO VALOR ENTERO CON SU SIGNO: ";
	cin >> entero2;
	
	cout << "\nINTRODUZCA UN TERCER VALOR ENTERO CON SU SIGNO: ";
	cin >> entero3;
	
	if (entero1 + entero2 + entero3 >= 0){
		if (entero1==0 || entero2==0 || entero3 == 0){
		    cout << "REINCIE EL PROGRAMA Y NO DE NINGUN VALOR 0" << endl;
		    system ("PAUSE");
		    return 0;
			}
		cout << "PREDOMINA EL SIGNO +" << endl;
	    system ("PAUSE");
	    return 0;
    	}
    else if (entero1 + entero2 + entero3 <= 0){
    	if (entero1==0 || entero2==0 || entero3 == 0){
		    cout << "REINCIE EL PROGRAMA Y NO DE NINGUN VALOR 0" << endl;
		    system ("PAUSE");
		    return 0;
			}
	    cout << "PREDOMINA EL SIGNO -" << endl;
        system ("PAUSE");
	    return 0;
    	}
	}
	
