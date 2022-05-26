#include <iostream>

using namespace std;

int main (){
	char vocal;
	int ascii;
	
	cout << "Pulse cualquier caracter del teclado para saber si es una vocal: ";
	cin >> vocal;
	
	ascii = vocal;
	
	if (ascii == 65 || ascii == 97){
		if(ascii==65){
			cout << "\n\tEL CARACTER INTRODUCIDO ES LA VOCAL 'A' (MAYUSCULA)" << endl; 
		}
		
		else {
			cout << "\n\tEL CARACTER INTRODUCIDO ES LA VOCAL 'a' (MINUSUCULA)" << endl;
		}
		
		system ("PAUSE");
		return 0;
	}
	
	else if (ascii == 69 || ascii == 101){
		if(ascii==69){
			cout << "\n\tEL CARACTER INTRODUCIDO ES LA VOCAL 'E' (MAYUSCULA)" << endl; 
		}
		
		else {
			cout << "\n\tEL CARACTER INTRODUCIDO ES LA VOCAL 'e' (MINUSUCULA)" << endl;
		}
		
		system ("PAUSE");
		return 0;
	}	

	else if (ascii == 73 || ascii == 105){
		if(ascii==73){
			cout << "\n\tEL CARACTER INTRODUCIDO ES LA VOCAL 'I' (MAYUSCULA)" << endl; 
		}
		
		else {
			cout << "\n\tEL CARACTER INTRODUCIDO ES LA VOCAL 'i' (MINUSUCULA)" << endl;
		}
		
		system ("PAUSE");
		return 0;
	}
		
	else if (ascii == 79 || ascii == 111){
		if(ascii==79){
			cout << "\n\tEL CARACTER INTRODUCIDO ES LA VOCAL 'O' (MAYUSCULA)" << endl; 
		}
		
		else {
			cout << "\n\tEL CARACTER INTRODUCIDO ES LA VOCAL 'o' (MINUSUCULA)" << endl;
		}
		
		system ("PAUSE");
		return 0;
	}

	else if (ascii == 85 || ascii == 117){
		if(ascii==85){
			cout << "\n\tEL CARACTER INTRODUCIDO ES LA VOCAL 'U' (MAYUSCULA)" << endl; 
		}
		
		else {
			cout << "\n\tEL CARACTER INTRODUCIDO ES LA VOCAL 'u' (MINUSUCULA)" << endl;
		}
		
		system ("PAUSE");
		return 0;
	}		
	
	else {
		cout << "\n\tNO SE HA INTRODUCIDO NINGUNA VOCAL" << endl;
		system ("PAUSE");
		return 0;
	}

}

