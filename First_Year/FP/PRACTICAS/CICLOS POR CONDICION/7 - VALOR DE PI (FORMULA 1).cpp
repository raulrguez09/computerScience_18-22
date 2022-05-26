#include <iostream>
#include <cmath>
#include <stdlib.h>
using namespace std;

int main (){
	
int n=1,i=2;
double pi, precision, aproximado, aproximados;

precision = 0.01;
pi = 3.14159265358;
aproximado=1;
aproximados=2;

while (abs(pi - (4*aproximado)) >= 0.01){
	aproximado = aproximado + (pow(-1,n))/(2*n + 1);
	n++;
}

cout << "SE HAN NECESITADO " << n << " OPERACIONES PARA LLEGAR A " << 4*aproximado << endl;

while(abs(pi - aproximados) >= 0.01){
	aproximados= aproximados * pow(i,2)/((i-1)*(i+1));
	i=i+2;
}
cout << "\nSE HAN NECESITADO " << i << " OPERACIONES PARA EL SEGUNDO METODO, LLEGANDO A " << aproximados << endl << endl;
system ("PAUSE");
return 0;
}
