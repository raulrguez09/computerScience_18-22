#include <iostream>
using namespace std;

int main(){
	const int MAX=1000;
	int A[MAX], B[MAX];
	int util_A, util_B;
	int pos, k;
	bool encontrado=false, coincidiendo=true;
	
	do{
		cout << "INTRODUZCA EL NUMERO DE ELEMENTOS DE A: ";
		cin >> util_A;
	}while(util_A<=0 || util_A>MAX);
	
	do{
		cout << "INTRODUZCA EL NUMERO DE ELEMENTOS DE B: ";
		cin >> util_B;
	}while(util_B<=0 || util_B>util_A);
		
	cout << "INTRODUZCA AHORA EL VECTOR A: " << endl;
	for (int i=0; i<util_A; i++)
		cin >> A[i];
	cout << "INTRODUZCA AHORA EL VECTOR B: " << endl;
	for (int i=0; i<util_B;i++)
		cin >> B[i];
		
	for (int i=0; i<util_A && !encontrado;i++){
		for (k=0; k<util_B;k++){
			if (A[i]==B[k]){
				i++;
				coincidiendo=true;
			}
			else coincidiendo=false;
		}
		if (coincidiendo){
		encontrado=true;
		pos=i-util_B;
	}
	
	}
	if (encontrado)
	cout << "EL VECTOR B SE CONTIENE EN A Y COMIENZA EN LA POSICION " << pos+1 << endl;
	else
	cout << "EL VECTOR B NO SE CONTIENE EN A" << endl;
	system ("PAUSE");
	return 0;
	}
