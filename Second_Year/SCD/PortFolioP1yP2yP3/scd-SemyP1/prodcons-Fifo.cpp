// -----------------------------------------------------------------------------
// Sistemas concurrentes y Distribuidos.
// Práctica 1: Problema productor-consumidor (sol con FIFO)
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
// Variables globales

const unsigned 
   num_items = 15,                     // número de items
	tam_vec = 10 ;                      // tamaño del buffer
unsigned cont_prod[num_items] = {0},   // contadores de verificación: datos producidos.
         cont_cons[num_items] = {0},   // contadores de verificación: datos consumidos.
         siguiente_dato = 0,           // siguiente dato a producir en 'producir_dato' (solo se usa ahí)
         primera_libre = 0,            // índice de la primera celda libre del vector (inicialmente 0)
         primera_ocupada = 0;          // índice de la primera celda ocupada del vector (inicialmente 0)

int vec[tam_vec];
Semaphore libres = tam_vec,            // 10 + #L - #E
	       ocupadas = 0;                // #E - #L

//**********************************************************************
// funciones comunes a las dos soluciones (fifo y lifo)
//----------------------------------------------------------------------
unsigned producir_dato()
{
   this_thread::sleep_for( chrono::milliseconds( aleatorio<20,100>() ));
   const unsigned dato_producido = siguiente_dato ;
   siguiente_dato++ ;
   cont_prod[dato_producido] ++ ;
   
   cout << "producido: " << dato_producido << endl << flush ;
   
   return dato_producido ;
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
   cout << endl << "comprobando contadores ..." ;
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
void  funcion_hebra_productora(  ){
   for( unsigned i = 0 ; i < num_items ; i++ ){
      int dato = producir_dato();                  // Producimos el dato
      sem_wait(libres);                            // Comprobamos si hay posiciones libres para insertar
      primera_libre %= 10;                         // Modulo tam vec (para ir al inicio)
      vec[primera_libre] = dato;                   // Insertamos el dato
      primera_libre++;                             // Aumentamos el índice de la primera libre (escribir)
      sem_signal(ocupadas);                        // Ocupamos una posición del vec
   }
}

//----------------------------------------------------------------------
void funcion_hebra_consumidora(  ){
   for( unsigned i = 0 ; i < num_items ; i++ ){
      int dato;                                    
      sem_wait(ocupadas);                          // Miramos si hay pos ocupada para consumir
      primera_ocupada %= 10;                       // Modulo tam vec (para ir al inicio)
      dato = vec[primera_ocupada];                 // Extraemos valor del vec (leer)
      vec[primera_ocupada] = 0;                    // Eliminamos elemento del vec
      primera_ocupada++;                           // Señalamos a la nueva primera pos ocupada
      consumir_dato(dato);                         // Consumimos el dato
      sem_signal(libres);                          // Nueva pos libre
   }
}

//----------------------------------------------------------------------
int main()
{
   cout << "-----------------------------------------------------------------" << endl
        << "Problema de los productores-consumidores (solución FIFO)." << endl
        << "------------------------------------------------------------------" << endl
        << flush ;

   thread hebra_productora ( funcion_hebra_productora ),
          hebra_consumidora( funcion_hebra_consumidora );

   hebra_productora.join() ;
   hebra_consumidora.join() ;

   test_contadores();
}