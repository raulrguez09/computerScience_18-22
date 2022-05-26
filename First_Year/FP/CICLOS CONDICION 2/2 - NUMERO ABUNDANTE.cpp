/* Un Número Abundante es un número cuyos divisores propios (todos los divisores excepto el
propio número) suman más que dicho número. Un ejemplo es 24, porque es menor que
1+2+3+4+6+8+12. Realizar un programa que muestre por pantalla los primeros 50 números
abundantes. */

#include <iostream>
using namespace std;

int main (){
	bool seguir=true;
	int numero=2,suma=0, contador=0;
	
	while (seguir){
	
		for (int i=1; i<numero;i++){
			if (numero%i==0)
				suma=suma+i;
		}
	
	if (suma > numero){
		cout << "\n--> " << numero;
		suma=0;
		contador++;
		numero++;
		if (contador==50)
			seguir=false;
	}
	else 
		numero++;	
		suma=0;
}
}
