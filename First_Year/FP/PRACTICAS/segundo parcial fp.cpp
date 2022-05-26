#include<iostream>
using namespace std;

int main(){
   
/*INICIALIZACIONES*/

const int MAX=50;
int m[MAX][MAX];
int V[MAX];
int utilF, utilC;
int filamayor=0, maximopares=0;
int FILA[MAX];
int intercambia;
bool cambio;

do{
cout << "INTRODUZCA EL NUMERO DE FILAS A INTRODUCIR: ";
cin >> utilF;
}while(utilF<=0 || utilF >MAX);


do{
cout << "INTRODUZCA EL NUMERO DE COLUMNAS A INTRODUCIR: ";
cin >> utilC;
}while(utilC<=0 || utilC >MAX);

cout << "INTRODUZCA PUES LA MATRIZ: " << endl;

for(int f=0; f<utilF; f++)
   for(int c=0; c<utilC; c++){
      do{
      cout << "m(" << f+1 << "," << c+1 << ")--> "; //SUMAMOS 1 A COLUMNAS Y FILAS PARA MAYOR ENTENDIMIENTO DEL USUARIO.
      cin >> m[f][c];
      }while(m[f][c] <= 0); //NO PERMITIMOS INTRODUCIR ELEMENTOS IGUALES O MENORES A 0.
   }
   
   
/*PROCESAMIENTO DE DATOS*/

for (int f=0; f<utilF; f++){
   V[f]=0;
   for(int c=0; c<utilC; c++){
      if (m[f][c]%2==0){ //SI SE DETECTA UN ELEMENTO PAR EN UNA FILA, SE SUMA EL CONTADOR DE PARES POR FILA (EN EL VECTOR).
          V[f]++;  
      }
   }
   if (V[f]>maximopares){
      maximopares=V[f];
      filamayor=f;
   }
}

//AHORA PROCEDEMOS A ORDENAR LA FILA CON MAYOR NÚMERO DE PARES: 

//ANTES, INTRODUCIMOS LA FILA CON MAYOR NÚMERO DE PARES EN UN VECTOR: 
for (int c=0; c<utilC; c++){
   FILA[c]=m[filamayor][c];
}

//AHORA REALIZAMOS SU ORDENACIÓN POR BURBUJA: 
cambio = true;
for (int izda = 0; izda < utilC && cambio; izda++){
   cambio = false;
   for (int i = utilC-1 ; i > izda ; i--){
      if (FILA[i] > FILA[i-1]){
         cambio = true;
         intercambia = FILA[i];
         FILA[i] = FILA[i-1];
         FILA[i-1] = intercambia;
      }
   }
}

/*SALIDA DEL PROGRAMA*/
cout << "LA MATRIZ INTRODUCIDA ES:" << endl;

for (int f=0; f<utilF; f++){
   for (int c=0; c<utilC; c++)
      cout << m[f][c] << " ";
   cout << endl;
}

cout << "\nLA FILA SELECCIONADA ES LA " << filamayor +1 << " QUE POR ORDEN DECRECIENTE QUEDARÍA: " << endl; //SUMAMOS UNO A LA FILA PARA MEJOR ENTENDIMIENTO DEL USUARIO.

for (int i=0; i<utilC; i++)
   cout << FILA[i] << " ";

if (V[filamayor]>0)
   cout << "\n(CON UN TOTAL DE " << V[filamayor] << " ELEMENTOS PARES)" <<endl;
else
   cout << "\n(SELECCIONADA POR DEFECTO LA PRIMERA FILA, PUES LA MATRIZ NO CONTIENE ELEMENTOS PARES)" << endl;

system("PAUSE");
return 0;

}
