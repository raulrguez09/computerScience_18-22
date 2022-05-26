#include <iostream>

using namespace std;

int main (){
int L;
int n;

cout << "INTRODUZCA EL NUMERO DE FILAS QUE QUIERE VISUALIZAR: ";
cin >> L;

for (n=1; n <= L; n++){
	int k=n;
	while (k>=10)
		k=k%10;
	
	for (int i=L-n; i>0; i--)
		cout << " ";
	
	for (int i=1; i<=(2*n-1); i++){

		if (i<=n){
			cout << k;
			if (k==9)
				k=0;
			else
				k++;
				
			if (i==n && k==0)
			k=8;
			if (i==n && k!=8)
			k=k-2;
		
		}
		else {
			if (k==-1)
			k=9;
		
			if (k==8)
			k=8;
				
			cout << k;
			k--;
		
		}
	}
	cout << endl;		
}
}
