#include<iostream>
using namespace std;

int main(){
	const int MAX_F=100, MAX_C=100;
	int m[MAX_F][MAX_C], utilF, utilC,tmpi;
	double V[MAX_C],tmpd;
	
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
	
	//LEER CON 2 FOR m
	for (int f = 0; f < utilF; f++)
		for (int c = 0; c < utilC; c++)
			cin >> m[f][c];
	
	// CALCULO DE MEDIAS
	for(int c=0; c<utilC; c++){
		V[c]=0;
		for(int f=0; f<utilF; f++)
			V[c]+=m[f][c];
		V[c] /= utilF;	
	}
	
	//ORDENACIÓN DEL VECTOR POR BURBUJA
	
	for(int izda=0; izda<utilC;izda++)
		for(int i=utilC-1;i>izda;i--)
			if(V[i-1]>V[i]){
				tmpd=V[i];
				V[i]=V[i-1];
				V[i-1]=tmpd;
				for (int f=0;f<utilF;f++){
					tmpi=m[f][i];
					m[f][i]=m[f][i-1];
					m[f][i-1]=tmpi;
				}
			}
			
	for (int i = 0; i < utilF; i++){
		for (int j = 0; j < utilC; j++)
			cout << m[i][j] << " ";
		cout << "\n";
}

system("PAUSE");
return 0;
}
