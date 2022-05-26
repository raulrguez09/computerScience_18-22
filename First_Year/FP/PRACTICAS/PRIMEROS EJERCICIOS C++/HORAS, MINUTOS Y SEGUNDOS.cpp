#include <iostream>

using namespace std;

int main (){
	
	int horas, minutos, segundos, h, m, s;
	
	cout << "\n Introduzca un numero de horas: ";
	cin >> horas;
	
	cout << "\n Introduzca un numero de minutos: ";
	cin >> minutos;
	
	cout << "\n Introduzca un numero de segundos: ";
	cin >> segundos;
	
	s = segundos % 60;
	m = (minutos % 60) + (segundos / 60);
	h = horas + (minutos/60);
	
	cout << "\n" << h << " h, " << m << " min y " << s << " s.";
	return 0;
	}
	
	
