#include<iostream>
using namespace std;

struct Complejo{
	double real;
	double imag;
};

int main(){
	Complejo c1, c2, suma;
	
	cout << "INTRODUZCA LA PARTE REAL DEL PRIMER COMPLEJO: ";
	cin >> c1.real;
	
	cout << "INTRODUZCA LA PARTE IMAG DEL PRIMER COMPLEJO: ";
	cin >> c1.imag;
	
	cout << "INTRODUZCA LA PARTE REAL DEL SEGUNDO COMPLEJO: ";
	cin >> c2.real;
	
	cout << "INTRODUZCA LA PARTE IMAG DEL SEGUNDO COMPLEJO: ";
	cin >> c2.imag;
	
	suma.real=c1.real+c2.real;
	suma.imag=c1.imag +c2.imag;
	if (suma.imag==0)
	cout << "LA SUMA RESULTANTE ES: " << suma.real;
	else
	cout << "LA SUMA RESULTANTE ES: " << suma.real << " " << suma.imag << "i";
	cout << endl;
	
	system("PAUSE");
	return 0;
}
