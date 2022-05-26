/** REALIZAR UN PROGRAMA QUE LEA DOS ENTEROS Y
 MUESTRE SU SUMA, RESTA, PRODUCTO, DIVISIÓN Y MÓDULO **/
 
 #include <iostream>
 using namespace std;
 
 int main (){
 	
    int entero1, entero2, suma, resta, producto, division, modulo;
    
    cout << "Introduzca un valor entero: ";
    cin >> entero1;
    
    cout << "\nIntroduzca un segundo valor entero: ";
    cin >> entero2;
    if (entero2 == 0){
    cout << "\n0 NO ES UN VALOR ENTERO";
	}
    
    suma = entero1 + entero2;
    
    resta = entero1 - entero2;
    
    producto = entero1 * entero2;
    
    division = entero1 / entero2;
    
    modulo = entero1 % entero2;
    
    cout << "\nSuma: " << suma << endl;
    cout << "\nResta: " << resta << endl;
    cout << "\nProducto: " << producto << endl;
    cout << "\nDivision: " << division << ", con un resto de: " << modulo;
    
    return 0;
    
 }
