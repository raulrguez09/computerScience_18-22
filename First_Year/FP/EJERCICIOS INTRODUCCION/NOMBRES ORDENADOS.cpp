#include <iostream>
#include <string>
using namespace std;

int main (){
    string nombre1, nombre2;
    
    cout << "INTRODUZCA UN NOMBRE COMPLETO: ";
    cin >> nombre1;
    
    cout << "INTRODUZCA OTRO NOMBRE COMPLETO: ";
    cin >> nombre2;
    
    if (nombre1<nombre2)
       cout << nombre1 << "\n" << nombre2;
       
    else cout << nombre2 << "\n" << nombre1;
    system ("PAUSE");
    return 0;
}
