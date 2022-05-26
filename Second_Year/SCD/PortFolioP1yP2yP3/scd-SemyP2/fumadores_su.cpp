// -----------------------------------------------------------------------------
// Sistemas concurrentes y Distribuidos.
// Practica 2: Problema de los fumadores (SU)
//
// Alumno: Raúl Rodríguez Pérez
// Curso: 21/22
// Clase: 2ºC
// -----------------------------------------------------------------------------

#include <iostream>
#include <iomanip>
#include <cassert>
#include <thread>
#include <random>
#include "scd.h"

using namespace std;
using namespace scd;

//-------------------------------------------------------------------------
// Función que simula la acción de producir un ingrediente, como un retardo
// aleatorio de la hebra (devuelve número de ingrediente producido)
//-------------------------------------------------------------------------
int ProducirIngrediente()
{
   // calcular milisegundos aleatorios para el retardo
   chrono::milliseconds duracion_produ( aleatorio<10,100>() );

   // informa de que comienza a producir
   //cout << endl << "Estanquero : empieza a producir ingrediente (" << duracion_produ.count() << " milisegundos)" << endl;
   
   // espera bloqueada un tiempo igual a ''duracion_produ' milisegundos
   this_thread::sleep_for( chrono::milliseconds( aleatorio<20,100>() ));
   
   // Producir ingrediene
   int num_ingrediente = aleatorio<0,2>() ;
   
   // informa de que ha terminado de producir
   cout << "Estanquero : termina de producir ingrediente " << num_ingrediente << endl;
   return num_ingrediente;
}

//------------------------------------------------------------------------------
// Función que simula la acción de fumar, como un retardo aleatoria de la hebra
//------------------------------------------------------------------------------
void Fumar( int num_fumador )
{
   // calcular milisegundos aleatorios del retardo
   chrono::milliseconds duracion_fumar( aleatorio<20,200>() );

   // informa de que comienza a fumar
   cout << "		Fumador " << num_fumador << "  :"
        << " empieza a fumar (" << duracion_fumar.count() << " milisegundos)" << endl;

   // espera bloqueada un tiempo igual a ''duracion_fumar' milisegundos
   this_thread::sleep_for( duracion_fumar );

   // informa de que ha terminado de fumar
   cout << "		Fumador " << num_fumador << "  : termina de fumar, comienza espera de ingrediente." << endl;
}

//------------------------------------------------------------------------------
// clase para monitor buffer -Estanco-, semántica SU.
//------------------------------------------------------------------------------
class Estanco : public HoareMonitor
{
   private:
      // Constantes:
      int ingr_actual;                    // Ingr actual en el mostrador
      
      // Colas condicion:
      CondVar ingr_disp[3],               // Condición para el ingr (ingr_actual != i -> (i = {0,1,2}))
              mostr_vacio;                // Condición para el mostrador vacío (ingr_actual != -1)

   // constructor y métodos públicos
   public:                    
      Estanco(  ) ;                       // Constructor
	   void obtenerIngrediente(int i);     // Obtener ingr
	   void ponerIngrediente( int i);      // Depositar ingr
	   void esperarRecogidaIngrediente();  // Esperar que recogan el ingr
};

// -----------------------------------------------------------------------------
// Constructor del estanco
//------------------------------------------------------------------------------
Estanco::Estanco(  )
{
   ingr_actual = -1;                  // Por defecto el mostrador está vacío
   mostr_vacio = newCondVar();

   for(int i=0; i<3; i++){
      ingr_disp[i] = newCondVar();
   }
}

// -----------------------------------------------------------------------------
// Función para retirar el ingr del mostrador o esperar
//------------------------------------------------------------------------------
void Estanco::obtenerIngrediente(int i)
{
	if(ingr_actual != i)                   // Si el ingr no es el que necesito, espero
	   ingr_disp[i].wait();

	ingr_actual = -1;                      // Como hemos recogido el ingr, el mostrador queda vacío
	cout << "Retirado igr.: "<< i <<endl;
	mostr_vacio.signal();

}

// -----------------------------------------------------------------------------
// Función para poner el ingr en el mostrador
//------------------------------------------------------------------------------
void Estanco::ponerIngrediente( int i)
{
	ingr_actual = i;                            // Ingr actual es el pasado por parámetro
	cout << "Puesto ingr.: " << i << endl;
	ingr_disp[i].signal();                    // Señalamos al fumador que esta esperando por el ingr	
}

// -----------------------------------------------------------------------------
// Función para que el estanquero espere la recogida del ingrediente
//------------------------------------------------------------------------------
void Estanco::esperarRecogidaIngrediente(){
	if(ingr_actual != -1)                       //Si el mostrador no está vacío, esperamos
	   mostr_vacio.wait();
}

// -----------------------------------------------------------------------------
// Función que ejecuta la hebra del estanquero
// -----------------------------------------------------------------------------
void funcion_hebra_estanquero(MRef<Estanco> estanco)
{
   int i;
	while(true){
	   i=ProducirIngrediente();
	   estanco->ponerIngrediente(i);
	   estanco->esperarRecogidaIngrediente();	
	}
}

// -----------------------------------------------------------------------------
// Función que ejecuta la hebra del fumador
// -----------------------------------------------------------------------------
void  funcion_hebra_fumador(MRef<Estanco> estanco, int num_fumador)
{
   while(true){
	   estanco->obtenerIngrediente(num_fumador);
	   Fumar(num_fumador);
   }
}

// -----------------------------------------------------------------------------
int main(){
   cout << "-------------------------------------------" << endl
        << "Problema de los fumadores (Monitor SU). " << endl
        << "-------------------------------------------" << endl
        << flush ;

   MRef<Estanco> monitor = Create<Estanco>();

   thread hebra_estanquero (funcion_hebra_estanquero, monitor),
	       hebra_fumador0(funcion_hebra_fumador,monitor,0),
	       hebra_fumador1(funcion_hebra_fumador,monitor,1),
	       hebra_fumador2(funcion_hebra_fumador,monitor,2);

   hebra_estanquero.join();
   hebra_fumador0.join();
   hebra_fumador1.join();
   hebra_fumador2.join();
}
