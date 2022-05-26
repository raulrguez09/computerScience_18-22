// -----------------------------------------------------------------------------
// Sistemas concurrentes y Distribuidos.
// Práctica 1: Problema productor-consumidor (sol con LIFO)
//
// Alumno: Raúl Rodríguez Pérez
// Curso: 21/22
// Clase: 2ºC
// -----------------------------------------------------------------------------

#include <iostream>
#include <cassert>
#include <thread>
#include <mutex>
#include <random>
#include "scd.h"

using namespace std;
using namespace scd;

//**********************************************************************
// variables compartidas

const int num_items = 40,                         // número de items
	       tam_vec   = 10;                         // tamaño del buffer
unsigned cont_prod[num_items] = {0},              // contadores de verificación: producidos
         cont_cons[num_items] = {0},              // contadores de verificación: consumidos
         primera_libre=0;                         // índice de la primera celda libre del vector (inicialmente 0)
int v[tam_vec];
Semaphore libres = tam_vec,                       // 10 + #L - #E
	       ocupadas=0;                             // #E - #L


//**********************************************************************
// funciones comunes a las dos soluciones (fifo y lifo)
//----------------------------------------------------------------------
int producir_dato()
{
   static int contador = 0 ;
   this_thread::sleep_for( chrono::milliseconds( aleatorio<20,100>() ));

   cout << "producido: " << contador << endl << flush ;

   cont_prod[contador] ++ ;
   return contador++ ;
}

//----------------------------------------------------------------------
void consumir_dato( unsigned dato )
{
   assert( dato < num_items );
   cont_cons[dato] ++ ;
   this_thread::sleep_for( chrono::milliseconds( aleatorio<20,100>() ));

   cout << "                  consumido: " << dato << endl ;

}

//----------------------------------------------------------------------
void test_contadores()
{
   bool ok = true ;
   cout << "comprobando contadores ...." ;
   for( unsigned i = 0 ; i < num_items ; i++ )
   {  if ( cont_prod[i] != 1 )
      {  cout << "error: valor " << i << " producido " << cont_prod[i] << " veces." << endl ;
         ok = false ;
      }
      if ( cont_cons[i] != 1 )
      {  cout << "error: valor " << i << " consumido " << cont_cons[i] << " veces" << endl ;
         ok = false ;
      }
   }
   if (ok)
      cout << endl << flush << "solución (aparentemente) correcta." << endl << flush ;
}

//----------------------------------------------------------------------
void  funcion_hebra_productora(  )
{
   for( unsigned i = 0 ; i < num_items ; i++ )
   {
      int dato = producir_dato() ;             // Producimos el dato
      sem_wait( libres );                      // Comprobamos si hay posiciones libres para insertar
      v[primera_libre]=dato;                   // Insertamos el dato
      primera_libre++;                         // Aumentamos el índice de la primera libre (escribir)
      sem_signal( ocupadas );                  // Ocupamos una posición del vec
   }
}

//----------------------------------------------------------------------
void funcion_hebra_consumidora(  )
{
   for( unsigned i = 0 ; i < num_items ; i++ )
   {
      int dato;
      sem_wait( ocupadas );                    // Miramos si hay pos ocupada para consumir
      dato=v[--primera_libre];                 // Extraemos valor del vec (leer)
      v[primera_libre]=0;                      // Eliminamos elemento del vec
      consumir_dato( dato ) ;                  // Consumimos el dato
      sem_signal( libres );                    // Nueva pos libre
      
    }
}

//----------------------------------------------------------------------
int main()
{
   cout << "--------------------------------------------------------" << endl
        << "Problema de los productores-consumidores (solución LIFO)." << endl
        << "--------------------------------------------------------" << endl
        << flush ;

   thread hebra_productora ( funcion_hebra_productora ),
          hebra_consumidora( funcion_hebra_consumidora );

   hebra_productora.join() ;
   hebra_consumidora.join() ;
   cout << "\nfin\n";

      test_contadores();
   cout << "vector temporal: ";
   for(int i=0; i<tam_vec; i++)
      cout << v[i] << " ";
   cout << endl;
}
