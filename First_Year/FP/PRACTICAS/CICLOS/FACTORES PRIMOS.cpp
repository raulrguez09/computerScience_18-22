#include <iostream>
using namespace std;

int main (){
	int n;
	int restante;
	int multiplicacion=1;
	cout << "INTRODUZCA UN NUMERO ENTERO PARA VER SU DESCOMPOSICION EN FACTORES PRIMOS: ";
	cin >> n;
	restante=n;
	
	cout << "\n" <<  n << " = ";
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
		restante=restante/i;
		multiplicacion=multiplicacion*i;
		if (multiplicacion==n)
		cout << i;
		else
		cout << i << " * ";
		
		}
		else
		i++;
	
}
}
