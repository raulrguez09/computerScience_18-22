#include<iostream>
#include<cmath>
using namespace std;

class Polinomio2G{
	private: 
		double grado2, grado1, independiente;
	public:
		void SetPolinomio(double gradodos, double gradouno, double terminoindependiente){
			grado2=gradodos;
			grado1=gradouno;
			independiente=terminoindependiente;
		}
		
		double TerminoGrado2(){
			return grado2;
		}
		
		double TerminoGrado1(){
			return grado1;
		}
		
		double TerminoIndependiente(){
			return independiente;
		}
		
		Polinomio2G SumaPolinomios(Polinomio2G polinomiouno){
			Polinomio2G polinomiosuma;
			
			polinomiosuma.SetPolinomio(polinomiouno.TerminoGrado2() + TerminoGrado2(), polinomiouno.TerminoGrado1()+TerminoGrado1(),polinomiouno.TerminoIndependiente()+TerminoIndependiente());
			return polinomiosuma;
		}
		
		Polinomio2G ProductoPorReal(double real){
			Polinomio2G polinomioproducto;
			polinomioproducto.SetPolinomio(real*TerminoGrado2(),real*TerminoGrado1(),real*TerminoIndependiente());
			return polinomioproducto;
		}
		
		void RaicesReales(){
			double raiz1;
			if (TerminoGrado2() != 0) {
				double denominador;
				double radicando;
			
				
				denominador = 2*TerminoGrado2();
				radicando = TerminoGrado1()*TerminoGrado1() - 4*TerminoGrado2()*TerminoIndependiente();
				
				if (radicando == 0){
					raiz1 = -TerminoGrado1() / denominador;
					cout << "\nSolo hay una raiz doble: " << raiz1;
				}
				else{
					if (radicando > 0){
						double radical;
						double raiz2;
						
						radical = sqrt(radicando);
						raiz1 = (-TerminoGrado1() + radical) / denominador;
						raiz2 = (-TerminoGrado1() - radical) / denominador;
						cout << "\nLas raices son" << raiz1 << " y " << raiz2;	
					}
					else
						cout << "\nNo hay raices reales.";
					}
			}
			else{
				if (TerminoGrado1() != 0){
					raiz1 = -TerminoIndependiente() / TerminoGrado1();
					cout << "\nEs una recta. La unica raiz es " << raiz1;
				}
				else
					cout << "\nNo es una ecuacion.";
				}
		}
		
};

int main(){
	
	Polinomio2G polinomio, suma, polinomia2;
	
	polinomio.SetPolinomio(6,4,9);
	
	polinomia2.SetPolinomio(2,9,2);
	
	suma=polinomio.SumaPolinomios(polinomia2);
	
	cout << "\n" << suma.TerminoGrado2() << "x^2 + " << suma.TerminoGrado1() << "x + " << suma.TerminoIndependiente() << "\n";
	
	Polinomio2G producto;
	
	producto=polinomio.ProductoPorReal(2);
	
	cout << "\n" << producto.TerminoGrado2() << "x^2 + " << producto.TerminoGrado1() << "x + " << producto.TerminoIndependiente() << "\n";
	
	polinomio.RaicesReales();
	
	suma.RaicesReales();
	
	polinomia2.RaicesReales();
	
	producto.RaicesReales();
	
	cout << endl;
	system("PAUSE");
	
	return 0;
	
}
