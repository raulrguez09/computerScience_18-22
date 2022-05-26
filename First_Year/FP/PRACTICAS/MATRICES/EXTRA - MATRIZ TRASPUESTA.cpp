#include<iostream>
using namespace std;

int main(){
	const int MAX=100;
	int utilF, utilC;
	int m[MAX][MAX], t[MAX][MAX];
	int utiltC, utiltF;
	do{
		cout << "INTRODUZCA EL NUMERO DE FILAS DE LA MATRIZ: ";
		cin >> utilF;
	}while(utilF<=0 || utilF>MAX);
	
	do{
		cout << "INTRODUZCA EL NUMERO DE COLUMNAS DE LA MATRIZ: ";
		cin >> utilC;
	}while(utilC<=0 || utilC>MAX);
	
	utiltC=utilF;
	utiltF=utilC;
	
	for (int f=0; f<utilF; f++){
		for (int c=0; c<utilC; c++){
			cout << "m(" << f+1 << "," << c+1 << ")--> ";
			cin >> m[f][c];
		}
		
		cout << endl;
	}
	
	cout << "VAMOS A CALCULAR LA TRASPUESTA DE LA MATRIZ: " << endl;
		
	for (int f=0; f<utilF; f++){
		for (int c=0; c<utilC; c++)
			cout << m[f][c] << " ";
		cout << endl;
	}
	
	for (int f=0; f<utilF; f++){
		for (int c=0; c<utilC; c++){
			t[c][f]=m[f][c];
		}
	}
	
	cout << "SIENDO ESTA: " << endl;
		
	for (int f=0; f<utiltF; f++){
		for (int c=0; c<utiltC; c++)
			cout << t[f][c] << " ";
		cout << endl;
	}
	
	
	
	system ("PAUSE");
	return 0;
}
