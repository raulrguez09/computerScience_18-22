#include<iostream>
using namespace std;

int main(){
	const int MAX=1000;
	int util_V, V[MAX];
	
	do{
		cout << "INTRODUZCA EL NUMERO DE ELEMENTOS A INTRODUCIR: ";
		cin >> util_V;
	}while(util_V>MAX);
	
	for (int i=0; i<util_V; i++)
		cin >> V[i];
	
	int tope=util_V;
	
	for (int i=0; i<tope; i++){
		int	k=2;
		bool ES_PRIMO=true;

		while (ES_PRIMO && k<V[i]){
			if (V[i]%k==0)
				ES_PRIMO=false;
			else 
				k++;
			}
			
		if (!ES_PRIMO){
			for (int h=i; h<util_V; h++)
				V[h]=V[h+1];
		
			util_V--;
		}
	}
	cout << endl << "ELIMINANDO LOS ELEMENTOS QUE NO SON PRIMOS QUEDA: ";
	
	for (int i=0; i<util_V; i++)
	cout << V[i] << " ";
	
	cout << endl;

	system("PAUSE");
	return 0;
}
