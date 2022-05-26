#include <iostream>
using namespace std;

int main (){
	int a, b, mcd, a0, a1, mayor, menor ;
	
	cout << "INTRODUZCA UN NUMERO ENTERO: ";
	cin >> a;
	
	cout << "\nINTRODUZCA OTRO NUMERO ENTERO: ";
	cin >> b;

	mayor=a;
	menor=b;
	if (a<b){
	mayor=b;
	menor=a;
    }
	
	a=mayor;
	b=menor;
	while (a1!=0){
			a0=b;
			a1=a%b;
			a=a0;
			b=a1;
	}
	mcd=a0;
	
	
	cout << "mcd(" << mayor << ", " << menor << "): " << mcd << endl;
	
	system ("PAUSE");
	return 0;
	
}
