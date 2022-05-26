/* REALIZAR UN PROGRAMA QUE LEA MIL CIRCUNFERENCIAS Y MUESTRE POR PANTALLA LA QUE 
TIENE MAYOR AREA */

#include<iostream>
#include<cmath>
using namespace std;
const double PI= 6 * asin(0.5);

class Circunferencia{
	private:
		double centro_x, centro_y;
		double radio;
	public:
		void SetCentro(double abscisa, double ordenada){
			centro_x=abscisa;
			centro_y=ordenada;
		}
		
		void SetRadio(double el_radio){
			radio=el_radio;
		}
		
		double AbscisaCentro(){
			return centro_x;
		}
		
		double OrdenadaCentro(){
			return centro_y;
		}
		
		double Radio(){
			return radio;
		}
		
		double Longitud(){
			return PI*radio;
		}
		
		double Area(){
			return PI*radio*radio;
		}
		
		void Traslada(double en_horizontal, double en_vertical){
			centro_x+=en_horizontal;
			centro_y+=en_vertical;
		}
};

int main(){
	Circunferencia c, cma;
	double xc, yc, r;
	int max;
	cout << "CUANTAS CIRCUNFERENCIAS QUIERE COMPARAR? ";
	cin >> max;
	for (int i=1; i<=max; i++){
		cout << "CIRCUNFERENCIA " << i << ": ";
		cout << "\n		CENTRO ABSCISA: ";
		cin >> xc;
		cout << "\n		CENTRO ORDENADA: ";
		cin >> yc;
		cout << "\n		RADIO: ";
		cin >> r;
		
		c.SetCentro(xc,yc);
		c.SetRadio(r);
		
		if (c.Area()>=cma.Area() || i==1){
			cma=c;
		}
	}
	
	cout << "\nLA CIRCUNFERENCIA CON MAYOR AREA ES LA DE CENTRO EN (" << cma.AbscisaCentro()
	<< "," << cma.OrdenadaCentro() << ") Y RADIO " << cma.Radio() << " CON UN AREA DE " << 
	cma.Area() << endl;
	
	system("PAUSE");
	return (0);
}
