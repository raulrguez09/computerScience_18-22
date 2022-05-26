#include<iostream>
using namespace std;

long long int Factorial(int n){
	long long int factorial=1;
	for (int i=1; i<=n; i++)
		factorial*=i;
	return (factorial);
}

int main(){
	int entero;
	
	cout << "INTRODUZCA UN ENTERO PARA SABER SU FACTORIAL: ";
	cin >> entero;
	
	cout << "\nEL FACTORIAL DE " << entero << " ES: " << Factorial(entero) << endl;
	
	system("PAUSE");
	return 0;
}
