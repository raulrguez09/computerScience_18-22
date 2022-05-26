#include<iostream>
using namespace std;

int MCD(int a, int b){
	int a0, a1, mayor, menor ;

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
	return (a0);
}

int main(){
	int a, b;
	
	cout << "INTRODUZCA DOS ENTEROS:" << endl;
	cin >> a;
	cin >> b;
	
	cout << "\nMCD(" << a << "," << b << ") = " << MCD(a,b) << endl;
	
	system ("PAUSE");
	return 0;
	
}
