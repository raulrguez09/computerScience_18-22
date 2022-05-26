#include<iostream>
using namespace std;

int main(){
	const int MAX=50;
	int m[MAX][MAX];
	int util_f, util_c;
	
	do{
		cout << "CUANTAS FILAS VA A INTRODUCIR?: ";
		cin >> util_f;
	}while(util_f<=0 || util_f>MAX);
	
	do{
		cout << "\nCUANTAS ELEMENTOS VA A INTRODUCIR COMO MAXIMO EN UNA FILA?: ";
		cin >> util_c;
	}while(util_c<=0 || util_c>MAX);
	
	cout << "\nINTRODUZCA LA MATRIZ DE DISTINTOS TAMANIOS: ";
	cout << "\n*CUANDO NO QUIERA INTRODUCIR MAS ELEMENTOS EN UNA FILA, RELLENELA DE CEROS*" << endl;
	
	for (int f = 0; f < util_f; f++)
		for (int c = 0; c < util_c; c++){
			do{
			cout << "m(" << f+1 << "," << c+1 << "): ";
			cin >> m[f][c];
			}while((c>0 && (m[f][c]>0 && m[f][c] <= m[f][c-1]) )||( c>0 && m[f][c] >= m[f][c-1]+2) || (c==0 && m[f][c]==0));
		}
		
	
		cout << "\nLA MATRIZ RESULTANTE ES: " << endl;
	for (int i = 0; i < util_f; i++){
		for (int j = 0; j < util_c; j++){
			if (m[i][j]==0)
				j=util_c;
			else
			cout << m[i][j] << " ";
		}
		cout << "\n";
	}
	
	int Vconcatenado[MAX], Vuno[MAX], Vdos[MAX];
	int utilconca=0, utiluno=0, utildos=0;
	
	for (int f=0; f<util_f; f++){
		for (int c=0; c<util_c; c++){
			if (m[f][c]!=0){
				Vuno[utiluno]=m[f][c];
				utiluno++;
			}
			for (int fila=0; fila<util_f; fila++){
				for (int co; co<util_c; co++)
				if (m[fila][0]>m[f][0] && m[fila][co]!=0){
					Vdos[utildos]=m[fila][co];
					utildos++;
				}
			}
			
		}
		
		if (utiluno+utildos>utilconca){
			utilconca=utiluno+utildos;
			for (int i=0; i<utiluno; i++){
				Vconcatenado[utilconca]=Vuno[i];
			}
			for (int i=0; i<utildos; i++)
				Vconcatenado[utilconca]=Vdos[i];
		}
	}	
	
	cout << "LA CONCATENACION MAYOR ES: ";
	for (int i=0; i<utilconca; i++)
		cout << Vconcatenado[i] << " ";
		
	cout << endl;
	
	system("PAUSE");
	return 0;


}
