#include <iostream>
using namespace std;

int main (){
	int entero, i, suma;
	bool es_suma=false;
	
	cout << "INTRODUZCA UN NUMERO ENTERO: ";
	cin >> entero;
	
	i=1;
	suma=0;
	
	while(i<entero && !es_suma){
		cout << "\n" << i << "+";
		suma=suma+i;
		if (suma==entero){
			es_suma=true;
			cout << "\n---";
			cout << "\n" << entero;
		}
		else 
		i++;
		
	}
	if (es_suma)
	cout << "\nEL NUMERO " << entero << " ES SUMA DE CONSECUTIVOS" << endl;
	else {
	cout << "\n!=";
	cout << "\n" << entero;
	cout << "\nEL NUMERO " << entero <<  " NO ES SUMA DE CONSECUTIVOS" << endl;
}
	system ("PAUSE");
	return 0;
}
