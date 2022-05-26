// PROGRAMA QUE LEE LOS LADOS DE UN TRIÁNGULO Y DA LA HIPOTENUSA

#include <iostream>
#include <cmath>
using namespace std;

int main () {
	double lado1, lado2, hipotenusa;
	
   cout << "INTRODUZCA EL VALOR DEL PRIMER CATETO: ";
   cin >> lado1;
   
   cout << "INTRODUZCA EL VALOR DEL SEGUNDO CATETO: ";
   cin >> lado2;
   
   hipotenusa = sqrt((lado1*lado1) + (lado2*lado2));
   
   cout << "\n LA HIPOTENUSA VALE: " << hipotenusa << endl;
   return 0;
}


