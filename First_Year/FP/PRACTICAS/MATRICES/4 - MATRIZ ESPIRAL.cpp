#include <iostream>
using namespace std;

int main(){
	const int MAX=50;
	int utilC, utilF;
	int m[MAX][MAX];
	
	do{
	cout << "INTRODUZCA LA DIMENSION DE LA MATRIZ CUADRADA (IMPAR): ";
	cin >> utilC;
	}while(utilC <= 0 || utilC > MAX || utilC%2==0);
	
	utilF=utilC;
	
	int i=1;
	int f=0;
	int c=0;
	int pasof=1;
	int pasoc=0;
	
	for(i,c,f,pasof,pasoc; i<=utilC*utilF;pasof++,pasoc++,f++,c++){
	for (c; c < utilC-pasoc; c++){
			m[f][c]=i;
			i++;
			}
	c--;
	i--;
	for (f; f<utilF-pasoc; f++ ){
		m[f][c]=i;
		i++;
		}
	f--;
	i--;
		
	for (c; c>=pasoc; c--){
		m[f][c]=i;
		i++;
		}
	c++;
	i--;
	
	for (f; f>=pasof; f--){
		m[f][c]=i;
		i++;
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
