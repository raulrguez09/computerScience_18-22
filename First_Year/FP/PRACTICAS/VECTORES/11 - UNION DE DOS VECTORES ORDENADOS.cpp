#include <iostream>
using namespace std;

int main(){
	const int MAX=1000;
	double V[MAX], P[MAX], ORDEN[MAX];
	int util_V, util_P, util_ORDEN;
	
	do{
		cout << "INTRODUZCA EL NUMERO DE ELEMENTOS A INTRODUCIR EN EL 1er VECTOR: ";
		cin >> util_V;
	}while(util_V<=0 || util_V>MAX);
	
	for(int i=0; i<util_V;i++){
		do{
			cout << i << "--> ";
			cin >> V[i];
		}while(V[i-1]>V[i]);
	}
	
	do{
		cout << "INTRODUZCA EL NUMERO DE ELEMENTOS A INTRODUCIR EN EL 2o VECTOR: ";
		cin >> util_P;
	}while(util_P<=0 || util_P>MAX);
	
	for(int i=0; i<util_P;i++){
		do{
			cout << i << "--> ";
			cin >> P[i];
		}while(P[i-1]>P[i]);
	}
	
	util_ORDEN=util_V+util_P;
	int k=0, h=0;
	for (int i=0; i<util_ORDEN;i++){
		if (V[k]<P[h]){
			if(k<util_V){
			ORDEN[i]=V[k];
			k++;
		}
			else{
			ORDEN[i]=P[h];
			h++;
		}
	}
		else if(V[k]>=P[h]){
			if(h<util_P){
			ORDEN[i]=P[h];
			h++;
		}	
			else{
				ORDEN[i]=V[k];
				k++;
			}
	}
			
	}
	
	for(int i=0; i<util_ORDEN; i++)
	cout << ORDEN[i] << " ";
	cout << endl;
	
	system("PAUSE");
	return 0;
	
}
