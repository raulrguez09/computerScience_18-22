// -----------------------------------------------------------------------------
// Sistemas concurrentes y Distribuidos.
// Práctica 1: Problema de los fumadores
//
// Alumno: Raúl Rodríguez Pérez
// Curso: 21/22
// Clase: 2ºC
// -----------------------------------------------------------------------------

#include <iostream>
#include <cassert>
#include <thread>
#include <mutex>
#include <random> // dispositivos, generadores y distribuciones aleatorias
#include <chrono> // duraciones (duration), unidades de tiempo
#include "scd.h"

using namespace std ;
using namespace scd ;
 
const int num_fumadores = 3 ;             // numero de fumadores
Semaphore mostr_vacio = 1;                // Semaforo para el mostrador (1 -> vacío, 0 -> ocupado)
Semaphore ingr_disp[3] = {0,0,0};         // Semaforo para ingredientes (1 -> ingr i disponible mostr, 0 -> no disp mostr)

//-------------------------------------------------------------------------
// Función que simula la acción de producir un ingrediente, como un retardo
// aleatorio de la hebra (devuelve número de ingrediente producido)
int producir_ingrediente()
{
   // calcular milisegundos aleatorios de duración de la acción de fumar)
   chrono::milliseconds duracion_produ( aleatorio<10,100>() );

   // informa de que comienza a producir
   cout << "Estanquero : empieza a producir ingrediente (" << duracion_produ.count() << " milisegundos)" << endl;

   // espera bloqueada un tiempo igual a ''duracion_produ' milisegundos
   this_thread::sleep_for( duracion_produ );

   const int num_ingrediente = aleatorio<0,num_fumadores-1>() ;

   // informa de que ha terminado de producir
   cout << "Estanquero : termina de producir ingrediente " << num_ingrediente << endl;

   return num_ingrediente ;
}

//----------------------------------------------------------------------
// función que ejecuta la hebra del estanquero
void funcion_hebra_estanquero(){
   int i;
   while(true){
      i = producir_ingrediente();               // Simular la producción -> res: entero(0, 1 o 2)
      sem_wait(mostr_vacio);                    // Mostrador ocupado
      cout << "Puesto ingrediente: " << i << endl;    // Sentencia Pi -> estanquero pone ingr en el mostr
      sem_signal(ingr_disp[i]);                 // Se manda una señal con el ingrediente producido 'i'
   }
}

//-------------------------------------------------------------------------
// Función que simula la acción de fumar, como un retardo aleatoria de la hebra
void fumar( int num_fumador ){

   // calcular milisegundos aleatorios de duración de la acción de fumar)
   chrono::milliseconds duracion_fumar( aleatorio<20,200>() );

   // informa de que comienza a fumar

    cout << "Fumador " << num_fumador << "  :"
          << " empieza a fumar (" << duracion_fumar.count() << " milisegundos)" << endl;

   // espera bloqueada un tiempo igual a ''duracion_fumar' milisegundos
   this_thread::sleep_for( duracion_fumar );

   // informa de que ha terminado de fumar

    cout << "Fumador " << num_fumador << "  : termina de fumar, comienza espera de ingrediente." << endl;

}

//----------------------------------------------------------------------
// función que ejecuta la hebra del fumador
void  funcion_hebra_fumador( int num_fumador ){
   while(true){
	   sem_wait(ingr_disp[num_fumador]);                  // Fumadores esperan a conseguir el ingrediente
	   cout << "Retirado ingrediente: "<< num_fumador<<endl;     // Sentencia Ri -> fumador retira el ingr 'i' del mostr
	   sem_signal(mostr_vacio);                           // Avisa al mostrador de que esta vacío
	   fumar(num_fumador);                                // Con todos los ingr el fumador puede fumar
   }
}

//----------------------------------------------------------------------

int main(){
   // se lanzan y hacen el join sobre las 4 hebras
   // declarar hebras y ponerlas en marcha

   thread hebra_estanquero (funcion_hebra_estanquero),
	hebra_fumador0(funcion_hebra_fumador,0),
	hebra_fumador1(funcion_hebra_fumador,1),
	hebra_fumador2(funcion_hebra_fumador,2);

   hebra_estanquero.join();
   hebra_fumador0.join();
   hebra_fumador1.join();
   hebra_fumador2.join();
}
