#include<iostream>
using namespace std;

int main(){
	const int MAX=1000;
	int V[MAX];
	int util_V, entero;
	
	do{
		cout << "INTRODUZCA EL NUMERO DE ELEMENTOS A INTRODUCIR: ";
		cin >> util_V;
	}while(util_V<=0 || util_V>MAX);
	
	cout << "INTRODUZCA PUES " << util_V << " ELEMENTOS: \n0--> ";
	cin >> V[0];
	for(int i=1; i<util_V; i++){
		do {
			cout << i << "--> ";
			cin >> V[i];
		}while(V[i]<V[i-1]);
	}
	
	for(int i=0; i<util_V; i++)
	cout << V[i] << " ";
	
	cout << endl;
	util_V++;
	
	cout << "\nQUE ELEMENTO QUIERE INTRODUCIR EN EL VECTOR?: ";
	cin >> entero;
	
	if(V[0]>entero){
		for(int k=util_V-1; k>=0; k--)
			V[k]=V[k-1];
		V[0]=entero;
	}
	
	else if(V[util_V-2]<=entero)
			V[util_V-1]=entero;
	else{
	for (int i=0; i<util_V; i++){
		if (entero>=V[i] && entero<=V[i+1] ){
			for (int k=util_V-1; k>i;k--)
				V[k]=V[k-1];
			V[i+1]=entero;
			i=util_V;
		}
	}
	}
	
	cout << "\nEL VECTOR RESULTANTE ES: \n";
	for (int i=0; i<util_V; i++)
		cout << V[i] << " ";
		
	cout << endl;
	
	system("PAUSE");
	return 0;
}
