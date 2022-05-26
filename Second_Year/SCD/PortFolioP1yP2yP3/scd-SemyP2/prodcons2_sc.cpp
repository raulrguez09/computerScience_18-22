// -----------------------------------------------------------------------------
// Sistemas concurrentes y Distribuidos.
// Seminario 2: Implementación múltiples prodCons SC (opción LIFO)
//
// Alumno: Raúl Rodríguez Pérez
// Curso: 21/22
// Clase: 2ºC
// -----------------------------------------------------------------------------

#include <iostream>
#include <iomanip>
#include <cassert>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <random>
#include "scd.h"

using namespace std ;
using namespace scd ;

constexpr int
   num_items  = 40 ,          // número de items a producir/consumir
   num_prods= 2,              // número de productores
   num_cons= 2;               // número de productores

int items_prods[num_prods],
	items_cons[num_cons];

mutex
   mtx ;                      // mutex de escritura en pantalla
unsigned
   cont_prod[num_items],      // contadores de verificación: producidos
   cont_cons[num_items];      // contadores de verificación: consumidos


//----------------------------------------------------------------------
// funciones comunes a las dos soluciones (fifo y lifo)
//----------------------------------------------------------------------
int producir_dato(int num_hebra_prod)
{
   int contador = items_prods[num_hebra_prod] + num_hebra_prod*num_items/num_prods ;
   this_thread::sleep_for( chrono::milliseconds( aleatorio<20,100>() ));
   mtx.lock();
   cout << "producido: " << contador << " por hebra " << num_hebra_prod << endl << flush ;
   mtx.unlock();
   cont_prod[contador] ++ ;
   items_prods[num_hebra_prod]++;
   return contador++ ;
}

//----------------------------------------------------------------------
void consumir_dato( unsigned dato, int num_hebra_con )
{
   if ( num_items <= dato )
   {
      cout << " dato === " << dato << ", num_items == " << num_items << endl ;
      assert( dato < num_items );
   }
   cont_cons[dato] ++ ;
   items_cons[num_hebra_con]++;
   this_thread::sleep_for( chrono::milliseconds( aleatorio<20,100>() ));
   mtx.lock();
   cout << "                          consumido: " << dato << " por hebra " << num_hebra_con << endl ;
   mtx.unlock();
}

//----------------------------------------------------------------------
void ini_contadores()
{
   for( unsigned i = 0 ; i < num_items ; i++ )
   {  cont_prod[i] = 0 ;
      cont_cons[i] = 0 ;
   }
}

//----------------------------------------------------------------------
void test_contadores()
{
   bool ok = true ;
   cout << "comprobando contadores ...." << flush ;

   for( unsigned i = 0 ; i < num_items ; i++ )
   {
      if ( cont_prod[i] != 1 )
      {
         cout << "error: valor " << i << " producido " << cont_prod[i] << " veces." << endl ;
         ok = false ;
      }
      if ( cont_cons[i] != 1 )
      {
         cout << "error: valor " << i << " consumido " << cont_cons[i] << " veces" << endl ;
         ok = false ;
      }
   }
   if (ok)
      cout << endl << flush << "solución (aparentemente) correcta." << endl << flush ;
}

//----------------------------------------------------------------------------
// clase para monitor buffer, version LIFO, semántica SC, un prod. y un cons.
//----------------------------------------------------------------------------
class ProdCons1SC
{
 private:
 static const int           // constantes:
   num_celdas_total = 10;   //  núm. de entradas del buffer
 int                        // variables permanentes
   buffer[num_celdas_total],//  buffer de tamaño fijo, con los datos
   primera_libre ;          //  indice de celda de la próxima inserción
 mutex
   cerrojo_monitor ;        // cerrojo del monitor
 condition_variable         // colas condicion:
   ocupadas,                //  cola donde espera el consumidor (n>0)
   libres ;                 //  cola donde espera el productor  (n<num_celdas_total)

 public:                    // constructor y métodos públicos
   ProdCons1SC(  ) ;           // constructor
   int  leer();                // extraer un valor (sentencia L) (consumidor)
   void escribir( int valor ); // insertar un valor (sentencia E) (productor)
} ;

// -----------------------------------------------------------------------------
// Constructor del monitor
// -----------------------------------------------------------------------------
ProdCons1SC::ProdCons1SC(  )
{
   primera_libre = 0 ;
}

// -----------------------------------------------------------------------------
// función llamada por el consumidor para extraer un dato
// -----------------------------------------------------------------------------
int ProdCons1SC::leer(  )
{
   // ganar la exclusión mutua del monitor con una guarda
   unique_lock<mutex> guarda( cerrojo_monitor );

   // esperar bloqueado hasta que 0 < num_celdas_ocupadas
   while ( primera_libre == 0 )
      ocupadas.wait( guarda );

   // hacer la operación de lectura, actualizando estado del monitor
   assert( 0 < primera_libre  );
   primera_libre-- ;
   const int valor = buffer[primera_libre] ;


   // señalar al productor que hay un hueco libre, por si está esperando
   libres.notify_one();

   // devolver valor
   return valor ;
}

// -----------------------------------------------------------------------------
// Función llamada por el productor para insertar un dato (escribir)
// -----------------------------------------------------------------------------
void ProdCons1SC::escribir( int valor )
{
   // ganar la exclusión mutua del monitor con una guarda
   unique_lock<mutex> guarda( cerrojo_monitor );

   // esperar bloqueado hasta que num_celdas_ocupadas < num_celdas_total
   while ( primera_libre == num_celdas_total )
      libres.wait( guarda );

   //cout << "escribir: ocup == " << num_celdas_ocupadas << ", total == " << num_celdas_total << endl ;
   assert( primera_libre < num_celdas_total );

   // hacer la operación de inserción, actualizando estado del monitor
   buffer[primera_libre] = valor ;
   primera_libre++ ;

   // señalar al consumidor que ya hay una celda ocupada (por si esta esperando)
   ocupadas.notify_one();
}

//----------------------------------------------------------------------
// funciones de hebras
// -----------------------------------------------------------------------------
void funcion_hebra_productora( ProdCons1SC * monitor, int num_hebra_prod )
{
   for( unsigned i = 0 ; i < num_items/num_prods ; i++ )
   {
      int valor = producir_dato(num_hebra_prod) ;
      monitor->escribir( valor );
   }
}

// -----------------------------------------------------------------------------
void funcion_hebra_consumidora( ProdCons1SC * monitor, int num_hebra_con )
{
   for( unsigned i = 0 ; i < num_items/num_cons ; i++ )
   {
      int valor = monitor->leer();
      consumir_dato( valor, num_hebra_con ) ;
   }
}

// -----------------------------------------------------------------------------
int main()
{
   cout << "-------------------------------------------------------------------------------" << endl
        << "Problema de los productores-consumidores (varios prod/cons, Monitor SC, buffer LIFO). " << endl
        << "-------------------------------------------------------------------------------" << endl
        << flush ;

   ProdCons1SC monitor ;

   thread productores[num_prods], consumidores[num_cons];

for(int i=0; i<num_prods;i++){
	items_prods[i]=0;
	productores[i] = thread( funcion_hebra_productora, &monitor, i);
}

for(int i=0; i<num_cons;i++){
	items_prods[i]=0;
	consumidores[i] = thread( funcion_hebra_consumidora, &monitor, i);
}

for(int i=0; i<num_prods;i++)
	productores[i].join();


for(int i=0; i<num_cons;i++)
	consumidores[i].join();





   // comprobar que cada item se ha producido y consumido exactamente una vez
   test_contadores() ;
}
