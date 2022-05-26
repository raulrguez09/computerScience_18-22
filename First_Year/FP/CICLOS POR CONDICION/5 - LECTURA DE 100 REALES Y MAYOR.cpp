#include <iostream>
using namespace std;

int main (){
	
	int pos, pos_max;
	double real, mayor;
		
	cout << "INTRODUZCA REALES, PARARA CUANDO HAYA INTRODUCIDO 100 VALORES O UN REAL MAYOR QUE 1000: \n1 --> ";
	cin >> real;
	
	mayor=real;
	
	pos=2;
	pos_max=pos;
	
	while(pos<=100 && real<1000){
		cout << "\n" << pos << " --> ";
		cin >> real;
		
		if (real < 1000 && mayor<real) {
			mayor=real;
			pos_max=pos;
		}	
		pos++;
	}
	
	cout << "EL MAYOR REAL LEIDO ES " << mayor << " Y SE ENCUENTRA EN LA POSICION " << pos_max << endl;
	system ("PAUSE");
	return 0;
	
	
	
}
