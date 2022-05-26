#include <iostream>
using namespace std;

int main (){
	int L=6;
	
	for (int n=1; n<=L;n++){
		for (int i=L;i>=n;i--)
		cout << "*";
		for (int i=1;i<=L-n;i++)
		cout << " ";
		cout << endl;
	}
	
	cout << "\n" << endl;
	system ("PAUSE");
	return 0;
	
}
