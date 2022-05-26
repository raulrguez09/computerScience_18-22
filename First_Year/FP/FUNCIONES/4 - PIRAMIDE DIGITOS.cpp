#include<iostream>
using namespace std;

void LINEA(int n){
	for (int i=1; i<=n;i++)
		cout << i%10;
}
void ESPACIOS(int p){
	for (int i=1; i<=p;i++)
		cout << " ";
}

void LINEAINVERSA(int n){
	for (int i=n-1; i>=1;i--)
		cout << i%10;
}

int main(){
	int L;
	
	cout << "INTRODUZCA EL NUMERO DE FILAS: ";
	cin >> L;
	
	for (int i=1; i<=L;i++){
		ESPACIOS(L-i);
		LINEA(i);
		LINEAINVERSA(i);
		cout << endl;
	}
}
