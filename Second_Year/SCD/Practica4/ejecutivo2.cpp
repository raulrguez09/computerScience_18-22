// -----------------------------------------------------------------------------
// Sistemas concurrentes y Distribuidos.
// Práctica 4. Implementación de sistemas de tiempo real.
//
// Archivo: ejecutivo2.cpp
// Implementación del segundo ejemplo de ejecutivo cíclico:
//
// Datos de las tareas:
// -------------
// Ta.  T     C
// -------------
// A   500   100
// B   500   150
// C   1000  200
// D   2000  240
// -------------
//
// El ciclo principal dura T_M = 2000 ms ya que
// T_M = mcm(500, 500, 1000, 2000) = 2000
//
// Planificación (con Ts == 500 ms)
// *-------*-------*-----*-------*
// | A B D | A B C | A B | A B C |
// *-------*-------*-----*-------*
//   490ms   450ms  250ms  450ms
//
// Cuestiones del portafollio:
// 1. ¿Cual es el mínimo tiempo de espera que queda al final de las iteraciones del ciclo secundario con tu solución?
// El tiempo más corto de espera se encontraría justo al final del primer ciclo secundario, este sería de solo 10ms.
//
// 2. ¿Sería planificable si la tarea D tuviese un tiempo cómputo de 250ms?
// Sí que seguiría siendo planificable, incluso pordría mantener la misma solución. El único cambio que se 
// presentaría sería que el primer ciclo secundario, en lugar de durar 490 ms duraría 500 ms, es decir el ciclo completo.
//
// Alumno: Raúl Rodríguez Pérez
// Curso: 21/22
// Clase: 2ºC
// -----------------------------------------------------------------------------

#include <string>
#include <iostream> // cout, cerr
#include <thread>
#include <chrono> // utilidades de tiempo
#include <ratio> // std::ratio_divide

using namespace std ;
using namespace std::chrono ;
using namespace std::this_thread ;

// tipo para duraciones en segundos y milisegundos, en coma flotante:
//typedef duration<float,ratio<1,1>> seconds_f ;
typedef duration<float,ratio<1,1000>> milliseconds_f ;

// -----------------------------------------------------------------------------
// tarea genérica: duerme durante un intervalo de tiempo (de determinada duración)

void Tarea( const std::string & nombre, milliseconds tcomputo )
{
   cout << "   Comienza tarea " << nombre << " (C == " << tcomputo.count() << " ms.) ... " ;
   sleep_for( tcomputo );
   cout << "fin." << endl ;
}

// -----------------------------------------------------------------------------
// tareas concretas del problema:
void TareaA() { Tarea( "A", milliseconds(100) ); }
void TareaB() { Tarea( "B", milliseconds(150) ); }
void TareaC() { Tarea( "C", milliseconds(200) ); }
void TareaD() { Tarea( "D", milliseconds(240) ); }

// -----------------------------------------------------------------------------
// implementación del ejecutivo cíclico:
int main( int argc, char *argv[] )
{
    // Ts = duración del ciclo secundario
    const milliseconds Ts( 500 );

    // ini_sec = instante de inicio de la iteración actual del ciclo secundario
    time_point<steady_clock> ini_sec = steady_clock::now();
    
    while( true ) // ciclo principal
    {
        cout << endl
        << "---------------------------------------" << endl
        << "Comienza iteración del ciclo principal." << endl ;

        for( int i = 1 ; i <= 4 ; i++ ) // ciclo secundario (4 iteraciones)
        {
            cout << endl << "Comienza iteración " << i << " del ciclo secundario." << endl ;

            switch( i ){
                case 1 : TareaA(); TareaB(); TareaD(); break ;
                case 2 : TareaA(); TareaB(); TareaC(); break ;
                case 3 : TareaA(); TareaB();           break ;
                case 4 : TareaA(); TareaB(); TareaC(); break ;
            }

            // calcular el siguiente instante de inicio del ciclo secundario
            ini_sec += Ts ;

            // esperar hasta el inicio de la siguiente iteración del ciclo secundario
            sleep_until( ini_sec );
            
            // Instante final actual
            time_point<steady_clock> fin_sec = steady_clock::now();

            // fin_sec - ini_sec (instante final esperado)
            steady_clock::duration duracion = fin_sec - ini_sec;

            cout << "El retraso es de " << milliseconds_f(duracion).count() << " milisegundos" << endl;
        }
    }
}
