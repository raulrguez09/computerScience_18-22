#include <iostream>
using namespace std;

int main (){
	int contador3max=0, max, iteracion, enteros;
	
	cout << "INTRODUZCA EL NUMERO DE ENTEROS QUE QUIERE COMPARAR: ";
	cin >> enteros;
	
	do {
		int n;
		int restante;
		int multiplicacion=1;
		int contador3=0;
		
		cout << "\nINTRODUZCA UN NUMERO ENTERO: ";
		cin >> n;
		
		restante=n;
	
		cout <<  n << " = ";
		
		for (int i=2; multiplicacion != n;){
			int k=2;
			bool es_primo=true;
			while (k<i && es_primo){
				if (i%k==0)
					es_primo=false;
				else
					k++;
			}
			if (es_primo && restante%i==0){
				if (i==3)
					contador3++;
		
				restante=restante/i;
				multiplicacion=multiplicacion*i;
				if (multiplicacion==n)
					cout << i << endl;
				else
					cout << i << " * ";
		
			}
			else
				i++;
		}
		
		iteracion++;
		if (contador3>contador3max){
			contador3max=contador3;
			max=n;
		}
	}
	while (iteracion!=enteros);

	cout << "\nEL NUMERO CON MAS '3' EN SU DESCOMPOSICION ES: " << max << endl;
	
	system ("PAUSE");
	return 0;
}
