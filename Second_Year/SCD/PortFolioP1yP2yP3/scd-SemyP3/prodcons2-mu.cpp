// -----------------------------------------------------------------------------
// Sistemas concurrentes y Distribuidos.
// Práctica 3. Implementación de algoritmos distribuidos con MPI
//
// Archivo: prodcons2-mu.cpp
// Implementación del problema del productor-consumidor  
// (versión con varios productores y varios consumidores)
//
// Alumno: Raúl Rodríguez Pérez
// Curso: 21/22
// Clase: 2ºC
// -----------------------------------------------------------------------------

#include <iostream>
#include <thread>                      // this_thread::sleep_for
#include <random>                      // dispositivos, generadores y distribuciones aleatorias
#include <chrono>                      // duraciones (duration), unidades de tiempo
#include <mpi.h>

using namespace std;
using namespace std::this_thread ;
using namespace std::chrono ;

const int
   np			 = 4,                      // Productores
   nc			 = 5,                      // Consumidores
   id_buffer             = 4 ,         // id_buffer == np
   num_procesos_esperado = 10 ,        // Número de procesos esperando
   num_items             = 20,         // num_items = múltiplo de np y nc
   tam_vector            = 10,         // Tamaño del vector del buffer
   etiq_producir	 = 4,                // Número de la etiqueta producir
   etiq_consumir	 = 5,                // Número de la etiqueta consumir
   k = num_items/np;                   // Número de valores producidos por cada productor 


//**********************************************************************
// plantilla de función para generar un entero aleatorio uniformemente
// distribuido entre dos valores enteros, ambos incluidos
// (ambos tienen que ser dos constantes, conocidas en tiempo de compilación)
//----------------------------------------------------------------------
template< int min, int max > int aleatorio()
{
  static default_random_engine generador( (random_device())() );
  static uniform_int_distribution<int> distribucion_uniforme( min, max ) ;
  return distribucion_uniforme( generador );
}

// ---------------------------------------------------------------------
// Función que producir produce los numeros en secuencia (1,2,3,....)
// ---------------------------------------------------------------------
int producir(int id)
{
   static int contador = id*k;
   sleep_for( milliseconds( aleatorio<10,100>()) );
   contador++ ;
   cout << "Productor " << id << " ha producido valor " << contador << endl << flush;
   return contador ;
}

// ---------------------------------------------------------------------
// Función de los productores
// ---------------------------------------------------------------------
void funcion_productor(int id)
{
   for ( int i= 0 ; i < num_items/np ; i++ )
   {
      // Producir valor
      int valor_prod = producir(id);
      // Enviar valor al buffer con la etiqueta de producir
      cout << "Productor va a enviar valor " << valor_prod << endl << flush;
      MPI_Ssend( &valor_prod, 1, MPI_INT, id_buffer, etiq_producir, MPI_COMM_WORLD );
   }
}


// ---------------------------------------------------------------------
// Función que consume un valor tras un retardo aleatorio
// ---------------------------------------------------------------------
void consumir( int valor_cons, int id)
{
   // espera bloqueada
   sleep_for( milliseconds( aleatorio<110,200>()) );
   cout << "          ----Consumidor " << id << " ha consumido valor " << valor_cons << endl << flush ;
}

// ---------------------------------------------------------------------
// Función que realiza los consumidores
// ---------------------------------------------------------------------
void funcion_consumidor(int id)
{
   int         peticion,
               valor_rec = 1 ;
   MPI_Status  estado ;

   for( unsigned int i=0 ; i < num_items/nc; i++ ){
      // Enviar petición al buffer con etiqueta de consumir
      MPI_Ssend( &peticion,  1, MPI_INT, id_buffer, etiq_consumir, MPI_COMM_WORLD);
      // Esperar recepción del valor a recibir por el buffer
      MPI_Recv ( &valor_rec, 1, MPI_INT, id_buffer, etiq_consumir, MPI_COMM_WORLD,&estado );
      // Consumir valor recibido
      cout << "             Consumidor " << id << " ha recibido valor " << valor_rec << endl << flush ;
      consumir( valor_rec, id );
   }
}

// ---------------------------------------------------------------------
// Función del buffer
// ---------------------------------------------------------------------
void funcion_buffer()
{
   int      buffer[tam_vector],         // buffer con celdas ocupadas y vacías
            valor,                      // valor recibido o enviado
            primera_libre       = 0,    // índice de primera celda libre
            primera_ocupada     = 0,    // índice de primera celda ocupada
            num_celdas_ocupadas = 0,    // número de celdas ocupadas
            etiq_aceptable ,            // identificador de etiqueta aceptable
	         id;                         // identificador del proceso
  MPI_Status estado ;                   // metadatos del mensaje recibido

   for( unsigned int i=0 ; i < num_items*2; i++ )
   {
      // 1. determinar si puede enviar solo prod., solo cons, o todos

      if ( num_celdas_ocupadas == 0 )                    // si buffer vacío
         etiq_aceptable = etiq_producir ;                   // $~~~$ solo prod.
      else if ( num_celdas_ocupadas == tam_vector )      // si buffer lleno
         etiq_aceptable = etiq_consumir ;                   // $~~~$ solo cons.
      else                                               // si no vacío ni lleno
         etiq_aceptable = MPI_ANY_TAG ;                     // $~~~$ cualquiera

      // 2. recibir un mensaje del emisor o emisores aceptables y almacenar su id

      MPI_Recv( &valor, 1, MPI_INT, MPI_ANY_SOURCE, etiq_aceptable, MPI_COMM_WORLD, &estado);
      id = estado.MPI_SOURCE;
      
      // 3. procesar el mensaje recibido

      switch( estado.MPI_TAG ) // leer etiqueta del mensaje en metadatos
      {
         case etiq_producir: // si ha sido un productor: insertar valor en buffer
            buffer[primera_libre] = valor ;
            primera_libre = (primera_libre+1) % tam_vector ;
            num_celdas_ocupadas++ ;
            cout << "   Buffer ha recibido valor " << valor << " del productor " << id << endl ;
            break;

         case etiq_consumir: // si ha sido un consumidor: extraer y enviarle el valor
            valor = buffer[primera_ocupada] ;
            primera_ocupada = (primera_ocupada+1) % tam_vector ;
            num_celdas_ocupadas-- ;            
            cout << "   Buffer va a enviar valor " << valor << " al consumidor " << id << endl ;
            MPI_Ssend( &valor, 1, MPI_INT, id, etiq_consumir, MPI_COMM_WORLD);
            break;
      }
   }
}

// ---------------------------------------------------------------------
int main( int argc, char *argv[] )
{
   int id_propio, num_procesos_actual;

   // inicializar MPI, leer identif. de proceso y número de procesos
   MPI_Init( &argc, &argv );
   MPI_Comm_rank( MPI_COMM_WORLD, &id_propio );
   MPI_Comm_size( MPI_COMM_WORLD, &num_procesos_actual );

   if ( num_procesos_esperado == num_procesos_actual ){
      // ejecutar la operación apropiada a 'id_propio'
      if ( id_propio < np )
         funcion_productor(id_propio);          // coincide con sus números de orden
      else if ( id_propio == id_buffer )
         funcion_buffer();
      else
         funcion_consumidor(id_propio);
   }
   else
   {
      if ( id_propio == 0 ) // solo el primero escribe error, indep. del rol
      { cout << "el número de procesos esperados es:    " << num_procesos_esperado << endl
             << "el número de procesos en ejecución es: " << num_procesos_actual << endl
             << "(programa abortado)" << endl ;
      }
   }

   // al terminar el proceso, finalizar MPI
   MPI_Finalize( );
   return 0;
}
