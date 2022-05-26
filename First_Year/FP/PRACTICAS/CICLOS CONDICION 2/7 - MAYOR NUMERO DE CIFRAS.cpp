#include <iostream>
using namespace std;

int main (){
	int x, x_tmp, x_max, contador, contador_max, x_normal;
	
	cout << "INTRODUZCA VALORES, CUANDO QUIERA PARAR, INTRUDUZCA 0: ";
	cout << "\n--> ";
	cin >> x_tmp;
	
	contador_max=0;
	x=x_tmp;
	
	while (x!=0){
		contador=1;
		x_normal=x;
		while (x/10!=0){
			x=x/10;
			contador++;
		}
		
		if (contador>contador_max){
		contador_max=contador;
		x_max=x_normal;
	}
		
		cout << "\n--> ";
		cin >> x;
		
		
	}
	
	cout << "EL NUMERO CON MAYOR NUMERO DE CIFRAS ES " <<  x_max << " CON " << contador_max;
	system ("PAUSE");
	return 0;	
}
