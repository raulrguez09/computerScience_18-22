/**
   @file Cálculo de la transpuesta de una matriz por el método de divide y vencerás.
*/

// Compilar con: g++ -std=c++11 DyVtraspuesta_ctime.cpp -o DyVtraspuesta_ctime

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>

using namespace std;

static int const MAX_VAL  = 50;   //Máximo valor de un elemento de la matriz


/**********************************************************************/

/**
   @brief Reserva espacio en memoria dinámica para una matriz cuadrada.
   
   @param dim: dimensión de la matriz. dim > 0.

   @returns puntero a la zona de memoria reservada.
*/
int ** ReservaMatriz(int dim);

/**********************************************************************/

/**
   @brief Libera el espacio asignado a una matriz cuadrada.
   
   @param M: puntero a la zona de memoria reservada. Es MODIFICADO.
   @param dim: dimensión de la matriz. dim > 0.

   Liberar la zona memoria asignada a M y lo pone a NULL.
*/
void LiberaMatriz(int ** & M, int dim);

/**********************************************************************/

/**
   @brief Rellena una matriz cuadrada con valores aleaotorias.
   
   @param M: puntero a la zona de memoria reservada. Es MODIFICADO.
   @param dim: dimensión de la matriz. dim > 0.

   Asigna un valor aleatorio entero de [0, MAX_VAL - 1] a cada
   elemento de la matriz M
*/
void RellenaMatriz(int ** M, int dim);

/**********************************************************************/

/**
   @brief Intercambia la submatriz "A" que empieza en la fila "filIniA"
          y  columna "colIniA" de la matriz "M" y que tiene de dimensión "dimen"
          por la  submatriz "B" que empieza en la fila "filIniB" y columna
          "colIniB" de la matriz "M" y que tiene de dimensión "dimen".
   
   @param M: puntero a la zona de memoria reservada. Es MODIFICADO.
   @param filIniA: fila de la matriz "M" donde empieza la submatriz "A".
   @param colIniA: columna de la matriz "M" donde empieza la submatriz "A".
   @param filIniB: fila de la matriz "M" donde empieza la submatriz "B".
   @param colIniB: columna de la matriz "M" donde empieza la submatriz "B".
   @param dimen: dimensión de la matriz "M". dim > 0.
*/
void swap (int ** & M,int filIniA, int colIniA, int filIniB, int colIniB, int dimen);

/**********************************************************************/

/**
   @brief Clacula la traspuesta de una submatriz "A" de la matriz "M".
   
   @param M: puntero a la zona de memoria reservada. Es MODIFICADO.
   @param filInicio: fila de la matriz "M" donde empieza la submatriz "A".
   @param filFin: fila de la matriz "M" donde termina la submatriz "A".
   @param colInicio: columna de la matriz "M" donde empieza la submatriz "A".
   @param colFin: columna de la matriz "M" donde termina la submatriz "A".
*/
void DyVtrasponer (int ** & M, int filInicio, int filFin, int colInicio, int colFin);

/**********************************************************************/

/**
   Implementación de las funciones
**/

int ** ReservaMatriz(int dim)
{
  int ** M;
  if (dim  <= 0)
    {
      cerr<< "\n ERROR: Dimension de la matriz debe ser mayor que 0 y potencia de 2" << endl;
      exit(1);
    }
  M = new int * [dim];
  if (M == NULL)
    {
      cerr << "\n ERROR: No puedo reservar memoria para un matriz de "
	   << dim << " x " << dim << "elementos" << endl;
      exit(1);
    }
  for (int i = 0; i < dim; i++)
    {
      M[i]= new int [dim];
      if (M[i] == NULL)
	{
	  cerr << "ERROR: No puedo reservar memoria para un matriz de "
	       << dim << " x " << dim << endl;
	  for (int j = 0; j < i; j++)
	    delete [] M[i];
	  delete [] M;
	  exit(1);
	} 
    }
  return M;
}

/**********************************************************************/

void LiberaMatriz(int ** & M, int dim)
{
  for (int i = 0; i < dim; i++)
    delete [] M[i];
  delete [] M;
  M = NULL;
}

/**********************************************************************/
void RellenaMatriz(int ** M, int dim)
{
  srand(time(NULL));
  
  for (int i = 0; i < dim; i++)
    for (int j = 0; j < dim; j++)
	    M[i][j]= (rand() % MAX_VAL);
}			


/**********************************************************************/

void swap (int ** & M,int filIniA, int colIniA, int filIniB, int colIniB, int dimen) {
    for (int i = 0; i < dimen; i++) {

        for (int j = 0; j < dimen; j++) {
            int aux = M[filIniA + i][colIniA + j];
            M[filIniA + i][colIniA + j] = M[filIniB + i][colIniB + j];
            M[filIniB + i][colIniB + j] = aux;
        }
    }
}


/**********************************************************************/

void DyVtrasponer (int ** & M, int filInicio, int filFin, int colInicio, int colFin) {

  int filMedio = (filInicio + filFin) / 2;
  int colMedio = (colInicio + colFin) / 2;

  // caso básico de matriz 2x2
  if (filFin - 1 == filInicio)
    swap (M, filMedio + 1, colInicio, filInicio, colMedio + 1, filFin - filMedio);
  
  else if (filFin - 1 > filInicio) {

    int filMedio = (filInicio + filFin) / 2;
    int colMedio = (colInicio + colFin) / 2;

    swap (M, filMedio + 1, colInicio, filInicio, colMedio + 1, filFin - filMedio);

    DyVtrasponer (M, filInicio, filMedio, colInicio, colMedio);
    DyVtrasponer (M, filInicio, filMedio, colMedio + 1, colFin);
    DyVtrasponer (M, filMedio + 1, filFin, colInicio, colMedio);
    DyVtrasponer (M, filMedio + 1, filFin, colMedio + 1, colFin);
    
  }
}

int main(int argc, char * argv[]) {

    clock_t tantes;    // Valor del reloj antes de la ejecución
    clock_t tdespues;  // Valor del reloj despu�s de la ejecución
    int dim;           // Dimensión de la matriz

    if (argc !=2 ) { // Comprobación de argumentos
        cerr << "Formato " << argv[0] << " <dimension matriz cuadrada>" << endl;
        exit(EXIT_FAILURE);
    }

    dim = atoi(argv[1]);// Dimensión de la matriz

    if (dim <= 0) {	// Argumento incorrecto
        cerr << "\n ERROR: Dimension de la matriz debe ser mayor que 0" << endl;
        exit(EXIT_FAILURE);
    }

    int ** matriz = ReservaMatriz(dim);
    RellenaMatriz(matriz, dim);


    //Salida de la matriz original
    cout << endl;
    cout << "Matriz original:" << endl;

    for (int i = 0; i < dim; i++){
        cout << "\n";
        
        for (int j = 0; j < dim; j++)
            cout << matriz[i][j] << '\t';
   }

    // Empieza el algoritmo de cálculo de la transpuesta
    tantes = clock();
    DyVtrasponer (matriz, 0, dim - 1, 0, dim - 1);
    tdespues = clock();

    //Salida de la matriz transpuesta
    cout << endl << endl;
    cout << "Matriz transpuesta:" << endl;

    for (int i = 0; i < dim; i++){
        cout << "\n";
        
        for (int j = 0; j < dim; j++)
            cout << matriz[i][j] << '\t';
   }

    cout << endl << endl;
    cout << dim << "\t" << ((double)(tdespues-tantes))/CLOCKS_PER_SEC << endl;
    LiberaMatriz(matriz, dim);

    cout << endl;

    return 0;
}
