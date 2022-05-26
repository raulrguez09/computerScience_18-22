#include <iostream>
using namespace std;

int main (){
int L;
int n;

cout << "INTRODUZCA EL NUMERO DE FILAS QUE QUIERE VISUALIZAR: ";
cin >> L;

for (n=1; n <= L; n++){
	int k=n;
	while (k>10)
		k=k%10;
	
	for (int i=L-n; i>0; i--)
		cout << " ";
	
	for (int i=1; i<=(2*n-1); i++){

		if (i<=n){
			if (k==0)
			k=10;
			cout << k-1;
			k--;
		}
		else {
			cout << k+1;
			if (k==8)
				k=-1;
			else
				k++;
		}
		
	}
	cout << endl;

	
	
}
}
