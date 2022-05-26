/* CREAR UNA CLASE CIRCUNFERENCIA */

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
	Circunferencia circunf;
	double x, y, radio;
	cout << "INTRODUZCA LAS COORDENADAS DEL CENTRO, PRIMERO X Y LUEGO Y: ";
	cin >> x;
	cin >> y;
	
	circunf.SetCentro(x,y);
	
	cout << "\nINTRODUZCA EL RADIO DE ESTA: ";
	cin >> radio;
	
	circunf.SetRadio(radio);
	
	cout << "\nLA CIRCUNFERENCIA DE RADIO " << circunf.Radio() << " CON CENTRO EN (" << circunf.AbscisaCentro() 
		<< "," << circunf.OrdenadaCentro() << ") TIENE PERIMETRO " << circunf.Longitud() << " Y AREA " 
		<< circunf.Area() << endl;
		
	system("PAUSE");
	return 0;
	
	
	
}
