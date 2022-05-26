#include <iostream>

using namespace std;

int main (){
	double a, b, operacion;
    int ascii;
    char opcion;
    
    cout << "INTRODUZCA UN VALOR REAL: ";
    cin >> a;
    
    cout << "\nINTRODUZCA OTRO VALOR REAL: ";
    cin >> b;
    
    cout << "\n\tQUE OPERACION DESEA REALIZAR " << a << " () " << b <<endl;
    
    cout << "\n- SUMAR (S)" << endl << "\n- RESTAR (R)" << endl << "\n- MULTIPLICAR (M)" << endl
    << "\n- DIVIDIR (D)" << endl;
    cin >> opcion;
    
    ascii = opcion;
    
    if ((ascii == 68 || ascii == 100) || (ascii == 77 || ascii == 109) ||
	 (ascii == 82 || ascii == 114) || (ascii == 83 || ascii == 115)){
    	if (ascii == 68 || ascii == 100){
    		operacion = a / b;
    		cout << "\nLA OPERACION ELEGIDA ES LA DIVISION: " << a << " / " << b << " = " << operacion << endl;
		}
		
		else if (ascii == 77 || ascii == 109){
    		operacion = a * b;
    		cout << "\nLA OPERACION ELEGIDA ES LA MULTIPLICACION: " << a << " * " << b << " = " << operacion << endl;
		}
		
		else if (ascii == 82 || ascii == 114){
    		operacion = a - b;
    		cout << "\nLA OPERACION ELEGIDA ES LA RESTA: " << a << " - " << b << " = " << operacion << endl;
		}
		
		else if (ascii == 83 || ascii == 115){
    		operacion = a + b;
    		cout << "\nLA OPERACION ELEGIDA ES LA SUMA: " << a << " + " << b << " = " << operacion << endl;
		}
		system ("PAUSE");
		return 0;
	}
	
    else {
    	cout << "\nPOR FAVOR, REINICIE EL PROGRAMA Y ELIJA UNA DE LAS OPCIONES PROPUESTAS" << endl;
    	system ("PAUSE");
    	return 0;
	}
}
