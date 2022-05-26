#include <iostream>
using namespace std;

int main (){
bool son_primos=false;
int maximo, n, x;

do{
	cout << "INTRODUZCA UN VALOR PARA HALLAR LOS PRIMOS GEMELOS MENORES QUE EL: ";
 	cin >> x;
} while (x<3);
n=-2;
for (int maximo=n+2; maximo<x; maximo++){
n=maximo+1;

while(! son_primos){
	if (es_primo(n) && es_primo(n+2))
	son_primos=true;
	else {
	son_primos=false;
	n++;
}
}
else
n++;
}
cout << n << " y " << n+2 << " ";
}}
