#include <iostream>
using namespace std;

int main (){
	int L=6;
	
	for (int n=1; n<=L;n++){
		for (int i=1;( n==1 || n==L) && i<L;i++)
		cout << "*";
		for (int i=n; i==n; i++)
		cout << "*";
		for (int i=2;i<L;i++)
		cout << " ";
		for (int i=L;n>=2 && n<L && i==L;i++)
		cout << "*";
		cout << endl;
	}
	
	cout << "\n" << endl;
	
	system ("PAUSE");
	return 0;
	
}
