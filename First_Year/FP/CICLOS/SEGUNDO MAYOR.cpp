/*Dise�ar un programa que lea n n�meros reales y muestre por pantalla el segundo elemento
mayor (el m�s cercano al mayor dato que es menor a �ste).*/

#include <iostream>

using namespace std;

int main(){
	int i, n;
	double introducido, cercano, mayor;
	
	cout << "CUANTOS REALES QUIERE INTRODUCIR?: ";
	cin >> n;
	cout << "INTRODUZCA " << n << " REALES: " << endl;
	cin >> mayor;
	cercano=-mayor;
	i=1;
	while (i<n){
	cin >> introducido;
	
	if (introducido<mayor && introducido>cercano){
	    cercano=introducido;

    }
    
    else if (introducido>mayor && introducido>cercano){
            cercano = mayor;
	   	    mayor=introducido;

}
    
    i++;
}

	cout << "EL NUMERO MAS CERCANO AL MAYOR ES: " << cercano << endl;
	system ("PAUSE");
	return 0;
}
