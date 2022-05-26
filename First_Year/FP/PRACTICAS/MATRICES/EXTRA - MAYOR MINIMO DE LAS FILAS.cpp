#include<iostream>
using namespace std;

struct posicion{
	int columna;
	int fila;
};

int main(){
	const int MAX=100;
	int utilF, utilC;
	int m[MAX][MAX];
	int minimo;
	int mayor=0;
	
	posicion posminimo, posmayor;
	
	do{
		cout << "INTRODUZCA EL NUMERO DE FILAS DE LA MATRIZ: ";
		cin >> utilF;
	}while(utilF<=0 || utilF>MAX);
	
	do{
		cout << "INTRODUZCA EL NUMERO DE COLUMNAS DE LA MATRIZ: ";
		cin >> utilC;
	}while(utilC<=0 || utilC>MAX);
	
	for (int f=0; f<utilF; f++){
		for (int c=0; c<utilC; c++){
			cout << "m(" << f+1 << "," << c+1 << ")--> ";
			cin >> m[f][c];
		}
		
		cout << endl;
	}
	
	for (int f=0; f<utilF; f++){
		int c=0;
		minimo=m[f][c];
		posminimo.columna=c;
		posminimo.fila=f;
		for (c=1; c<utilC; c++){
			if (m[f][c]<minimo){
				minimo=m[f][c];
				posminimo.columna=c;
				posminimo.fila=f;
			}
		}
		if (minimo>mayor){
			mayor=minimo;
			posmayor.columna=posminimo.columna;
			posmayor.fila=posminimo.fila;
		}
	}
		
	for (int f=0; f<utilF; f++){
		for (int c=0; c<utilC; c++)
			cout << m[f][c] << " ";
		cout << endl;
	}
	
	cout << "EL MAYOR DE LOS MINIMOS DE LAS FILAS ES " << mayor << " SITUADO EN (" << posmayor.fila+1 << "," << posmayor.columna+1 << ")" << endl;
	
	system ("PAUSE");
	return 0;
}
