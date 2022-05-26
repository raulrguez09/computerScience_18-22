#include <iostream>
using namespace std;

int main (){
	const int MAX=1000;
	int n, util_V, tmp, restante;
	int V[MAX];
	cout << "INTRODUZCA UN NUMERO ENTERO: ";
	cin >> n;
	
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
