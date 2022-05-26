/* Programa que pida un número y devuelva por pantalla
 un mensaje diciendo si es o no perfecto.*/

#include <iostream>

using namespace std;

int main (){
	
	int i, n, suma;
	
	cout << "INTRODUZCA UN NUMERO ENTERO POSITIVO: ";
	cin >> n;
	
	i=1;
	suma=0;
	 while (i<n){
		if (n%i==0){
			cout << "\n--> " << i;
			suma=suma+i;}
			
		i++;
	}
	
	if (suma==n)
	cout << "\n\t\t** EL NUMERO " << n << " ES PERFECTO **" << endl;
	else 
	cout << "\n\t\t** EL NUMERO " << n << " NO ES PERFECTO **" << endl;
	
	system ("PAUSE");
	return 0;

}
