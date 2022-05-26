#include <iostream>
using namespace std;

int main (){
bool es_primo1, es_primo2, encontrado=false;
int n, p, q;

do{
cout << "INTRODUZCA UN NUMERO ENTERO: ";
cin >> n;
}
while(n>2 && n%2!=0);

q=n-p;

for (p=2;p<=n/2 && !encontrado;p++){
	
	es_primo1=true;
	
	for (int i=2;i<p;i++){
		if(p%i==0)
		es_primo1=false;
	}
	
	q=n-p;
	es_primo2=true;
	
	for (int i=2;i<q;i++){
		if (q%i==0)
		es_primo2=false;
	}
	
	if (es_primo1 && es_primo2)
		encontrado=true;
	
	
	}
	p--;
	if (encontrado)
	cout << "SEGUN LA CONJETURA DE GOLDBACK, " << n << " ES IGUAL A " << p << " + " << q << endl;
	
	system ("PAUSE");
	return 0;
	
}
