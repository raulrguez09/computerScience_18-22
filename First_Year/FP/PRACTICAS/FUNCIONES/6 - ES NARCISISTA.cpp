#include <iostream>
#include <cmath>
using namespace std;


bool es_narcisista(int x){
	int numero, cifras, suma, i,restante;
	
	cifras=1;
	numero=x;
	while (x/10!=0){
		x=x/10;
		cifras++;
	}
	i=cifras-1;
	restante=numero;
	suma=0;
	while (i<cifras && i>=0){
		int long potencia10=pow(10,i);
		suma=suma+pow(restante/potencia10,cifras);
		i--;
		restante=restante-(potencia10*(restante/potencia10));
	}
	
	if (suma==numero)
		return (true);
	else
		return (false);
}
int main (){
	int x;
	
do {
	cout << "INTRODUZCA UN NUMERO NATURAL MENOR DE 1690: ";
	cin >> x;
} while (x>=1690);
		

	if (es_narcisista(x))
	cout << "\nEL NUMERO " << x << " ES NARCICISTA" << endl;
	else
	cout << "\nEL NUMERO " << x << " NO ES NARCISISTA" << endl;
	system ("PAUSE");
	return 0;	
}
