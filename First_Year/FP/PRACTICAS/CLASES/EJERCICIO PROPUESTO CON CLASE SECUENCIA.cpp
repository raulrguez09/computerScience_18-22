#include <iostream>
using namespace std;

class Secuencia_int{

private:
   static const int TAMANIO = 50;
   int vector_privado[TAMANIO];
   int total_utilizados;
   
public:
   Secuencia_int()
      :total_utilizados(0) {
   }
   
   int TotalUtilizados(){
      return total_utilizados;
   }
   
   int Capacidad(){
      return TAMANIO;
   }
   
   void EliminaTodos(){
      total_utilizados = 0;
   }
   
   void Aniade(int nuevo){
      if (total_utilizados < TAMANIO){
         vector_privado[total_utilizados] = nuevo;
         total_utilizados++;
      }
   }
   
   void Modifica(int posicion, int nuevo){
      if (posicion >= 0 && posicion < total_utilizados)
         vector_privado[posicion] = nuevo;
   }

   int Elemento(int indice){
      return vector_privado[indice];
   }
   

};
/*leer el vector, leer un i y busqueda y burbuja*/

int main()
{
	Secuencia_int V;
	int x;
	int buscando;
	
	//LEER VECTOR
	cout << "INTRODUCIR DATO: ";
	cin >> x;
	while(x!=0){
		V.Aniade(x);
		cout << "INTRODUCIR DATO: ";
		cin >> x;
	}
	//MOSTRAR VECTOR
	
	cout << endl << "EL VECTOR ES EL SIGUIENTE: ";
	for(int i=0; i<V.TotalUtilizados();i++)
		cout << V.Elemento(i) << " ";
	cout << endl;
	
	
	char opcion;
	bool quiere_buscar;
	
	do{
	cout << "QUIERE BUSCAR UN ELEMENTO EN EL VECTOR? \nPULSE S PARA SI, O N PARA NO: ";
	cin >> opcion;
	if (opcion == 'S' || opcion == 's')
		quiere_buscar=true;
		else if (opcion == 'N' || opcion == 'n')
			quiere_buscar=false;
		else
			opcion='o';
	}while(opcion=='o');
	
	if (quiere_buscar){
		cout << "QUE ELEMENTO QUIERE BUSCAR EN EL VECTOR?: ";
		cin >> buscando;
	
	//BUSQUEDA SECUENCIAL
		bool encontrado=false;
		int pos_encontrado;
	
		for (int i=0; i<V.TotalUtilizados() && !encontrado; i++){
			if (V.Elemento(i)==buscando){
				encontrado=true;
				pos_encontrado=i;
			}
		}
	
		if (encontrado)
			cout << "EL ELEMENTO " << buscando << " SE HA ENCONTRADO EN LA POSICION " << pos_encontrado << endl;
		else
			cout << "EL ELEMENTO " << buscando << "NO SE HA ENCONTRADO EN EL VECTOR" << endl;
	}
	
	//ORDENACIÓN POR BURBUJA
	int intercambia;
	
	for (int izda = 0; izda < V.TotalUtilizados(); izda++){
		for (int i = V.TotalUtilizados()-1 ; i > izda ; i--){
			if (V.Elemento(i) < V.Elemento(i-1)){
				intercambia = V.Elemento(i);
				V.Modifica(i,V.Elemento(i-1));
				V.Modifica(i-1,intercambia);
			}
		}
	}
	
	cout << endl << "POR ULTIMO, EL VECTOR ORDENADO QUEDARIA: ";
	for(int i=0; i<V.TotalUtilizados();i++)
		cout << V.Elemento(i) << " ";
	cout << endl;
	
	system("PAUSE");
	return 0;
}


 
