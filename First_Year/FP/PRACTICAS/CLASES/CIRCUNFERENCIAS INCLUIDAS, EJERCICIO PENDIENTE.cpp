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
		
		bool Incluida(Circunferencia C){
			if (pow(AbscisaCentro() - C.AbscisaCentro(),2)+pow(OrdenadaCentro() - C.OrdenadaCentro(),2) <= pow(C.Radio(),2))
				return true;
			else
				return false;
		}
		
		void Traslada(double en_horizontal, double en_vertical){
			centro_x+=en_horizontal;
			centro_y+=en_vertical;
		}
};

/*lEER UNA CIRCUNFERENCIA C Y LEER UN CONJUNTO DE CIRCUNFERENCIAS HASTA INTRODUCIR UNA CON RADIO 0. 
MOSTRAR POR PANTALLA LAS CIRCUNFERENCIAS QUE ESTÉN INCLUIDAS EN C */

/*INCLUIR METODO, bool Incluida(Circunferencia C).
(X1-X2)^2 + (Y1-Y2)^2 <= R^2 */

int main(){
	const int MAX=50;
	int util_V=0;
	Circunferencia V[MAX];
	Circunferencia C;
	Circunferencia circunf;

	//LECTURA DE C
	double xc, yc, radioc;
	cout << "INTRODUZCA LAS COORDENADAS DEL CENTRO DE C, PRIMERO X Y LUEGO Y: \n";
	cin >> xc;
	cin >> yc;

	C.SetCentro(xc,yc);
	
	cout << "\nINTRODUZCA EL RADIO DE ESTA: ";
	cin >> radioc;
	
	C.SetRadio(radioc);
	
	//LEER CIRCUNFERENCIAS E INCLUIR LAS INTERIORES EN UN VECTOR
	
	double x, y, radio;
	cout << "INTRODUZCA LAS COORDENADAS DEL CENTRO DE OTRA, PRIMERO X Y LUEGO Y:\n ";
	cin >> x;
	cin >> y;

	circunf.SetCentro(x,y);
	
	cout << "\nINTRODUZCA EL RADIO DE ESTA: ";
	cin >> radio;
	
	circunf.SetRadio(radio);
	
	while(circunf.Radio()!=0){
		if (circunf.Incluida(C)){
			V[util_V]=circunf;
			util_V++;
		}
	cout << "INTRODUZCA LAS COORDENADAS DEL CENTRO DE OTRA CIRCUNF, PRIMERO X Y LUEGO Y:\n ";
	cin >> x;
	cin >> y;

	circunf.SetCentro(x,y);
	
	cout << "\nINTRODUZCA EL RADIO DE ESTA: ";
	cin >> radio;
	
	circunf.SetRadio(radio);
	}
	
	cout << "LAS CIRCUNFERENCIAS CONTENIDAS EN LA C, DE RADIO " << C.Radio() << " Y CENTRO (" << C.AbscisaCentro() << "," << C.OrdenadaCentro() << ") SON: ";
	for (int i=0; i<util_V; i++){
		cout << "R:" << V[i].Radio() << "(" << V[i].AbscisaCentro() << "," << V[i].OrdenadaCentro() << ")  ";
	}
	
	cout << endl;
	
	system("PAUSE");
	return 0;
		
}


