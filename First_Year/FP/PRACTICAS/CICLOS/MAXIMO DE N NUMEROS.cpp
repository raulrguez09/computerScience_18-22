/* PROGRAMA QUE LEA n NUMEROS Y MUESTRE EL MAYOR DE ELL0S */

#include <iostream>

using namespace std;

int main (){
	
	int i, n;
	double x, max;
	
	cout << "CUANTOS NUMEROS QUIERE INTRODUCIR? : ";
	cin >> n;
	
	cout << "\n--> ";
	cin >> x;
	
	max = x;

    i = 1;
    while (i<n){
    	cout << "\n--> ";
    	cin >> x;
    	
    	if (x >= max){
    		max=x;
		}
    	
    	i++;
	}
	
	cout << "EL MAXIMO DE LOS INTRODUCIDOS ES: " << max <<endl;
	system ("PAUSE");
	return 0;
}
