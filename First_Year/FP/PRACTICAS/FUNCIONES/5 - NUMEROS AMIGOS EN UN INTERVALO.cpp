#include<iostream>
using namespace std;

void amigos(int inferior, int superior){
	for (int i=inferior+1; i<superior; i++){
		int suma=0;
		int suma2=0;
		for (int k=1; k<i; k++ ){
			if (i%k==0)
			suma=suma + k;
		}
		for (int h=1; h<suma; h++){
			if (suma%h==0)
				suma2=suma2+h;
		}
		if (suma2==i && suma!=i){
			cout << i << " y " << suma << endl;
			i=suma+1;
		}
	}
}

int main(){
	int inferior, superior;
	cout << "INTRODUZCA EL LIMITE INFERIOR: ";
	cin >> inferior;
	
	cout << "INTRODUZCA EL LIMITE SUPERIOR: ";
	cin >> superior;
	
	amigos(inferior,superior);
	
	system("PAUSE");
	return 0;
	
}
