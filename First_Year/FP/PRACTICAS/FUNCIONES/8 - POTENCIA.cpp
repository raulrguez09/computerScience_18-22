#include<iostream>
#include <stdlib.h>
using namespace std;

double Potencia(int n, int elevado){
	double potencia=1;
	for (int i=1; i<=abs(elevado); i++)
		potencia*=n;
	if (elevado>=0)
	return (potencia);
	else 
	return (1/potencia);
}

int main(){
	int entero, elevado;
	
	cout << "INTRODUZCA UN ENTERO: ";
	cin >> entero;
	cout << "A QUE QUIERE ELEVARLO: ";
	cin >> elevado;
	
	cout << "\n" << entero << "^" << elevado << " = " << Potencia(entero,elevado) << endl;
	
	system("PAUSE");
	return 0;
}
