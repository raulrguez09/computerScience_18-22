#include<iostream>
using namespace std;

int main(){
	const int MAX=1000;
	int V[MAX];
	int util_V, tmp;
	
	do{
		cout << "INTRODUZCA EL NUMERO DE ELEMENTOS A INTRODUCIR: ";
		cin >> util_V;
	}while(util_V<=0 || util_V>MAX);
	
	cout << "INTRODUZCA PUES " << util_V << " ELEMENTOS: \n";
	
	for(int i=0; i<util_V; i++){
		cout << "-->";
		cin >> V[i];
	}
	
	cout << endl;
	
	for (int i=0; i<util_V; i++){
		int h=i+1;
		for (int k=i; k>=0; k--)
				if (V[h]>V[k]){
					for (int j=util_V-1; j>=k;j--)
						V[j]=V[j-1];
					V[h]=V[k];
				}
	}
	
	cout << "EL VECTOR YA ORDENADO QUEDARIA: ";
	
	for (int i=0; i<util_V; i++)
	cout << V[i] << " ";
	
	cout << endl;
	
	system("PAUSE");
	return 0;
	
}
