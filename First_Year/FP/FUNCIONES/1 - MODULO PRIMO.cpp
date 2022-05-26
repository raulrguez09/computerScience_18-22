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

int main(){
int entero, p, q;
bool encontrado=false;

do{
	cout << "INTRODUZCA UN NUMERO ENTERO PAR MAYOR DE 2: ";
	cin >> entero;
}while(entero<=2 && entero%2!=0);

for (p=2;p<=entero/2 && !encontrado;p++){
	q=entero-p;
	
	if (es_primo(q) && es_primo(p))
		encontrado=true;
}
p--;
	if (encontrado)
	cout << "SEGUN LA CONJETURA DE GOLDBACK, " << entero << " ES IGUAL A " << p << " + " << q << endl;
	
	system ("PAUSE");
	return 0;
}
