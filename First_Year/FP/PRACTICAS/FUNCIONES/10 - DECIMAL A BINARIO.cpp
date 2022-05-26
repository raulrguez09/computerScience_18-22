#include <iostream>
using namespace std;

void A_BINARIO (int n){
	const int MAX=1000;
	int util_V=0, tmp, restante;
	int V[MAX];
	
	tmp=n;
	while (tmp/2 > 0){
	util_V++;
	tmp=tmp/2;
}
	util_V++;
	
	restante=n;
	
	for (int i=0; i<util_V; i++){
		V[i]=restante % 2;
		restante=restante/2;
	}
	
	
	for (int i=util_V-1; i>=0; i--)
	cout << V[i];
}

int main(){
	int n;
	
	cout << "INTRODUZCA UN NUMERO ENTERO PARA VER SU RESPECTIVO BINARIO: ";
	cin >> n;
	
	cout << n << " = ";
	A_BINARIO(n);
	cout << endl;
	
	system("PAUSE");
	return 0;
}
