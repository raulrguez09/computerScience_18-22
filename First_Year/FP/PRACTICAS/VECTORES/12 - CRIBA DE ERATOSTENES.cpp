#include <iostream>
using namespace std;

int main(){
	const int MAX=1000;
	int V[MAX];
	int util_V;
	int elemento=1;
	
	do{
		cout << "INTRODUZCA UN NUMERO ENTERO: ";
		cin >> util_V;
	}while(util_V<=0 || util_V>MAX);
	
	util_V--;
	
	for (int i=0; i<util_V; i++){
		V[i]=elemento;
		elemento++;
	}
		
	for (int i=1; i<util_V; i++){
		for(int k=i+1; k<util_V;k++){
			if (V[k]%V[i]==0){
				for(int h=k; h<util_V; h++)
					V[h]=V[h+1];
				
				util_V--;
			}
		}
	}
	for (int i=0; i<util_V; i++)
	cout << V[i] << " ";
	cout << endl;
	
	system("PAUSE");
	return 0;
}
