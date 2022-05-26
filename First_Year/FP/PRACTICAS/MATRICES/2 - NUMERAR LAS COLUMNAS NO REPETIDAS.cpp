#include<iostream>
using namespace std;

int main(){
	const int MAX_F=100, MAX_C=100;
	int m[MAX_F][MAX_C], utilF, utilC, contador;
	
	// LEER UTILF
	do{
		cout << "INTRODUZCA EL NUMERO DE FILAS A INTRODUCIR: ";
		cin >> utilF;
	}while(utilF<=0 || utilF>MAX_F);
	
	// LEER UTILC
		do{
		cout << "INTRODUZCA EL NUMERO DE COLUMNAS A INTRODUCIR: ";
		cin >> utilC;
	}while(utilC<=0 || utilC>MAX_C);
	
	contador=utilC;
	
	//LEER CON 2 FOR m
	for (int c = 0; c < utilC; c++)
		for (int f = 0; f < utilF; f++){
			cout << "m(" << f+1 << "," << c+1 << "): ";
			cin >> m[f][c];
		}
	
	cout << "\nLA MATRIZ RESULTANTE ES: " << endl;
	for (int i = 0; i < utilF; i++){
		for (int j = 0; j < utilC; j++)
			cout << m[i][j] << " ";
		cout << "\n";
	}
	int total=utilC;
	bool primeravez;
	
	for (int c = 0; c < utilC; c++){
		primeravez=true;
		for (int h = c+1; h < utilC; h++){
			bool seguir=true;
			for (int f=0; f<utilF && seguir; f++){
				if (m[f][c]!=m[f][h])
					seguir=false;
				
			}
				if (m[utilF][c]==m[utilF][h] && seguir){
					contador--;
					for (int ef=0; ef<utilF; ef++){
						for (int k=h; k<utilC;k++)
							m[ef][k]=m[ef][k+1];
					}
					
					utilC--;
					h--;
					
					if (primeravez){
						primeravez=false;
						contador--;
					}
					
				}
		}
		}
		
			cout << "\nLA MATRIZ SIN COLUMNAS REPETIDAS ES: " << endl;
		for (int i = 0; i < utilF; i++){
			for (int j = 0; j < utilC; j++)
				cout << m[i][j] << " ";
			cout << "\n";
		}
		
		
	
		cout << "\nDE LAS " << total << " COLUMNAS, " << contador << " NO SE REPITEN" << endl;
	
	
	system("PAUSE");
	return 0;
}
