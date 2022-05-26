#include <iostream>
using namespace std;

int main (){
	int L=7, impar=0, IMPAR=0;
	
	for(int n=1; n<=L; n++){
		if (n%2!=0)
		impar++;
		for (int i=4-impar; i>=0 && n%2!=0;i--)
		cout << " ";
		for (int i=0; i<n && n%2!=0;i++)
		cout << "*";
		cout << endl;
	}
	for(int n=L-1; n>0; n--){
		if (n%2!=0)
		IMPAR++;
		for (int i=IMPAR; i>=0 && n%2!=0;i--)
		cout << " ";
		for (int i=0; i<n && n%2!=0;i++)
		cout << "*";
		cout << endl;
	}
}
