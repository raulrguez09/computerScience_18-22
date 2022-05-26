#include <iostream>
using namespace std;

int main(){
	const int MAX=50;
	int m[MAX][MAX];
	int utilC, utilF;
	double Vmedia[MAX];
	int utilV;
	int tmpd, tmpi;
	do{
		cout << "INTRODUZCA EL NUMERO DE FILAS A LEER: ";
		cin >> utilF;
	}while(utilF<=0 || utilF>MAX);
	
	do{
		cout << "INTRODUZCA EL NUMERO DE COLUMNAS A LEER: ";
		cin >> utilC;
	}while(utilC<=0 || utilC>MAX);
	
	utilV=utilF;
	
	for (int f=0; f<utilF; f++)
		for (int c=0; c<utilC; c++){
			cout << "\nm(" << f+1 << ","	<< c+1 << ")--> ";
			cin >> m[f][c];
		}
		
	cout << "LA MATRIZ INTRODUCIDA ES:" << endl;
	
	for (int f=0; f<utilF; f++){
		for (int c=0; c<utilC; c++)
			cout << m[f][c] << " ";
		cout << endl;
	}
	
	for (int f=0; f<utilF; f++){
		int suma=0;
		for (int c=0; c<utilC; c++)
			suma=suma+m[f][c];
		double media=1.0*suma/utilC;
		Vmedia[f]=media;
	}
	
	for(int arriba=0; arriba<utilF;arriba++)
		for(int i=utilF-1;i>arriba;i--)
			if(Vmedia[i-1]>Vmedia[i]){
				tmpd=Vmedia[i];
				Vmedia[i]=Vmedia[i-1];
				Vmedia[i-1]=tmpd;
				for (int c=0;c<utilC;c++){
					tmpi=m[i][c];
					m[i][c]=m[i-1][c];
					m[i-1][c]=tmpi;
				}
			}
			
	cout << "LA MATRIZ ORDENADA SEGUN LA MEDIA DE LAS FILAS ES:" << endl;
	
	for (int f=0; f<utilF; f++){
		for (int c=0; c<utilC; c++)
			cout << m[f][c] << " ";
		cout << "  M: " << Vmedia[f] << endl;
	}
			
	
		
		system("PAUSE");
		return 0;
	
}
