#include<iostream>
using namespace std;

int main(){
	const int MAX=100;
	int A[MAX][MAX], B[MAX][MAX], C[MAX][MAX], n;
	
	
	// LEER UTILF
	do{
		cout << "INTRODUZCA EL NUMERO DE FILAS Y COLUMNAS DE AMBAS MATRICES: ";
		cin >> n;
	}while(n<=0 || n>MAX);
	
	//LEER CON 2 FOR A
	for (int f = 0; f < n; f++){
		cout << "INTRODUZCA LA FILA " << f << " DE A: \n";
		for (int c = 0; c < n; c++)
			cin >> A[f][c];
	}
	
	//LEER CON 2 FOR B
	for (int f = 0; f < n; f++){
		cout << "INTRODUZCA LA FILA " << f << " DE B: \n";
		for (int c = 0; c < n; c++)
			cin >> B[f][c];
	}
			
	for (int i=0; i<n;i++)
		for(int j=0; j<n; j++){
			C[i][j];
			for (int k=0; k<n; k++)
				C[i][j]+=A[i][k]*B[k][j];
		}
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++)
			cout << C[i][j] << " ";
		cout << "\n";
}
	}
