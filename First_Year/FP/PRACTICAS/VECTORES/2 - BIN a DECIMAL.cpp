#include <iostream>
#include <cmath>
using namespace std;

int main(){
	
	int util_V;
	const int MAX=1000;
	int V[MAX];
	int k;
	
	do{
		
	cout << "INTRODUZCA EL NUMERO DE DIGITOS A INTRODUCIR: ";
	cin >> util_V;
	
	}while(util_V>=MAX);
	
	cout << "INTRODUZCA " << util_V << " DIGITOS EN BINARIO: " << endl;
	
	for (int i=0; i<util_V;i++){
		do{
		cout << "\n--> ";
		cin >> V[i];
	}while (V[i]<0 || V[i]>1);
	}
	
	cout << endl;
	
	for (int i=0; i<util_V;i++){
		cout << V[i];
	}
	
	cout << " = ";
	int suma=0;
	k=util_V-1;
	
	for (int i=0; i<util_V;i++){
	if (V[i]==1){
		suma=suma+pow(2,k);
		k--;
	}
	else k--;
}
	cout << suma << endl;
	
	system("PAUSE");
	return 0;
}
