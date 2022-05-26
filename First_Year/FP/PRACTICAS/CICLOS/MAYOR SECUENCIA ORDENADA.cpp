/* REALIZAR UN PROGRAMA QUE LEA ENTEROS HASTA INTRODUCIR EL 0 Y MUESTRE
LA SECUENCIA ORDENADA DE MAYOR LONGITUD*/

#include <iostream>
using namespace std;

int main (){
	int i, n, anterior, inicio_mayor, fin_mayor, inicio_act, fin_act;
	
	cout << "Introduzca valores, cuando quiera parar introduzca 0: \n-->";
	cin >> n;
	
	fin_mayor=0;
	anterior=n;
	fin_act=0;
	inicio_act=1;
	
	while (n != 0){
		i++;
		if (n >= anterior)
			fin_act++;
		else {
			if (fin_act > fin_mayor){
		    	fin_mayor=fin_act;
		    	inicio_mayor=inicio_act;
		    }
			inicio_act=i;
			fin_act=1;
		}
		anterior=n;
		cout << "\n-->";
		cin >> n;	
	}
	
	if (fin_act > fin_mayor){
		    	fin_mayor=fin_act;
		    	inicio_mayor=inicio_act;
		    }
		    
	if (i == 0)
		    cout << "\nNO SE HAN INTRODUCIDO DATOS"	<< endl;
	else {
		cout << "\nCOMIENZO: " << inicio_mayor << " y LONGITUD: " << fin_mayor;
	}	    
	
}
