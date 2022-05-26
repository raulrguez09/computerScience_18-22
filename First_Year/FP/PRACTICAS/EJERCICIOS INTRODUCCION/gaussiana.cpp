#include <iostream>
#include <cmath>

using namespace std;

int main () {
    double media, desv, x, y;
    
    cout << "Introduzca la media: ";
    cin >> media;
    
    cout << "\nIntroduzca la desviacion tipica: ";
    cin >> desv;
    
    cout << "\nIntroduzca a continuacion un valor de abscisa: ";
    cin >> x;
    
    if (desv == 0){
    	cout << "\nLA FUNCION GAUSSIANA NO EXISTE PARA UN VALOR DE DESVIACION 0";
    	return 0;
	}
    
    y = (exp ((-1/2) * ((x - media)/desv) * ((x - media)/desv)))/(desv * sqrt(2 * 3.14159265358979323846));

    cout << "\ngaussiana (" << x << ") = " << y;
    return 0;
}
