#include<iostream>
using namespace std;

bool es_primo(int entero){
	int i=2;
	bool primo=true;
	while(i<entero && primo){
		if (entero%i==0)
			primo=false;
		else
			i++;
		
	}
	return (primo);
}
int main (){
bool son_primos=false;
int maximo, n, x;

do{
	cout << "INTRODUZCA UN VALOR PARA HALLAR LOS PRIMOS GEMELOS MENORES QUE EL: ";
 	cin >> x;
} while (x<3);
n=-2;
int doble;
for (int maximo=0; maximo<x ; maximo=n+2){
n=maximo+1;
if (es_primo(n) && es_primo(n+2) &&n+2<x){
cout << n << " y " << n+2 << "\n";
n++;}
else
n++;
}}
