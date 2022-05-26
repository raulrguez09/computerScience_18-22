#include <iostream>
using namespace std;

int main(){
	const int MAX=1000;
	int V[MAX];
	int MAYOR=0, POSMAYOR, k;
	int util_V;
	
	do{
		cout << "INTRODUZCA EL NUMERO DE ELEMENTOS QUE VA A INTRODUCIR: ";
		cin >> util_V;
	}while(util_V>MAX);
		
	for (int i=0; i<util_V; i++){
	cin >> V[i];
	k=2;
	
	bool ES_PRIMO=true;

	while (ES_PRIMO && k<V[i]){
			if (V[i]%k==0){
				ES_PRIMO=false;
			}
			else 
				k++;
			}
	if (ES_PRIMO && V[i]>MAYOR){
		MAYOR=V[i];
		POSMAYOR=i+1;
	}
}
	
	cout << "\nEL MAYOR PRIMO INTRODUCIDO ES: " << MAYOR << " EN LA POSICION " << POSMAYOR << endl;
	
	system("PAUSE");
	return 0;
}
