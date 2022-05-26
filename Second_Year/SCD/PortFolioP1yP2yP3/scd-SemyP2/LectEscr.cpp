// -----------------------------------------------------------------------------
// Sistemas concurrentes y Distribuidos.
// Práctica 2: Implementación lectores/escritores
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

const int numLectores = 3, numEscritores = 3;
mutex mtx;

//----------------------------------------------------------------------
void escribir( int escritor )
{
   chrono::milliseconds duracion( aleatorio<20,100>() );
   mtx.lock();
   cout << "ESCRITOR " << escritor << " ESCRIBIENDO ("<< duracion.count() << ")" << endl;
   mtx.unlock();
   this_thread::sleep_for( duracion );
}

//----------------------------------------------------------------------
void leer( int lector )
{
   chrono::milliseconds duracion( aleatorio<20,100>() );
   mtx.lock();
   cout << "LECTOR " << lector << " LEYENDO ("<< duracion.count() << ")" << endl;
   mtx.unlock();
   this_thread::sleep_for( duracion );
}

//----------------------------------------------------------------------
void terminarEscribir( int escritor )
{
   chrono::milliseconds duracion( aleatorio<20,100>() );
   mtx.lock();
   cout << "ESCRITOR " << escritor << " HA DEJADO DE ESCRIBIR ("<< duracion.count() << ")" << endl;
   mtx.unlock();
   this_thread::sleep_for( duracion );
}

//----------------------------------------------------------------------
void terminarLeer( int lector )
{
   chrono::milliseconds duracion( aleatorio<20,100>() );
   mtx.lock();
   cout << "LECTOR " << lector << " HA DEJADO DE LEER ("<< duracion.count() << ")" << endl;
   mtx.unlock();
   this_thread::sleep_for( duracion );
}

//---------------------------------------------------------------------------
// clase para monitor buffer, version LIFO, semántica SU, varios prod y cons.
//----------------------------------------------------------------------------
class LecEsc : public HoareMonitor
{
   private:
      int n_lec;
      bool escrib;
   
      CondVar lectura, escritura; 

   public:  
      LecEsc( );
      void iniLectura( ); 
      void finLectura( );
      void iniEscritura( ); 
      void finEscritura( );

} ;

LecEsc::LecEsc(  )
{
   n_lec = 0;
   escrib = false;
   lectura = newCondVar();
   escritura = newCondVar();
}

void LecEsc::iniLectura( )
{
   if ( escrib )
      lectura.wait();

   n_lec++;
   lectura.signal();
}

void LecEsc::finLectura( )
{
   n_lec--;
   if( n_lec == 0 )
      escritura.signal();
}

void LecEsc::iniEscritura( )
{
   if( n_lec > 0 || escrib )
      escritura.wait();
   escrib = true;
}

void LecEsc::finEscritura( )
{
   escrib = false;
   if( !lectura.empty() )
      lectura.signal();
   else 
      escritura.signal();
}

//----------------------------------------------------------------------
void funcion_hebra_escritor ( MRef<LecEsc> monitor, int escritor )
{
   while ( true ){
      monitor->iniEscritura();
      escribir(escritor);
      monitor->finEscritura();
      terminarEscribir(escritor);
   }
}

//----------------------------------------------------------------------
void funcion_hebra_lector ( MRef<LecEsc> monitor, int lector )
{
   while ( true ){
      monitor->iniLectura();
      leer(lector);
      monitor->finLectura();
      terminarLeer(lector);
   }
}

//----------------------------------------------------------------------
int main()
{
   thread escritores [ numEscritores ];
   thread lectores [ numLectores ] ;
   MRef<LecEsc> monitor = Create<LecEsc>();

   for( int i = 0; i < numEscritores; i++ ){
      escritores[i] = thread( funcion_hebra_escritor, monitor, i );
   }
   for( int i = 0; i < numLectores; i++ ){
      lectores[i] = thread( funcion_hebra_lector, monitor, i );
   }

   for( int i = 0; i < numEscritores; i++ ){
      escritores[i].join();
   }
   for( int i = 0; i < numLectores; i++ ){
      lectores[i].join();
   }
}
