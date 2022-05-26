#include<iostream>
using namespace std;

void LINEA(int n){
	for (int i=1; i<=n;i++)
		cout << "*";
}
void ESPACIOS(int p){
	for (int i=1; i<=p;i++)
		cout << " ";
}

int main(){
	int L;
	
	cout << "INTRODUZCA EL NUMERO DE FILAS: ";
	cin >> L;
	
	for (int i=0; i<=L;i++){
		ESPACIOS(i);
		LINEA(L-i);

		cout << endl;
	}
}
