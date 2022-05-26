// -----------------------------------------------------------------------------
// Sistemas concurrentes y Distribuidos.
// Práctica 3. Implementación de algoritmos distribuidos con MPI
//
// Archivo: filosofos-interb.cpp
// Implementación del problema de los filósofos (con camarero).
// Plantilla para completar.
//
// Alumno: Raúl Rodríguez Pérez
// Curso: 21/22
// Clase: 2ºC
// -----------------------------------------------------------------------------


#include <mpi.h>
#include <thread> // this_thread::sleep_for
#include <random> // dispositivos, generadores y distribuciones aleatorias
#include <chrono> // duraciones (duration), unidades de tiempo
#include <iostream>

using namespace std;
using namespace std::this_thread ;
using namespace std::chrono ;

const int
   num_borrachos = 10,
   num_procesos = 12, 
   id_dependiente = 10,
   id_cervecero = 11,
   etiq_reponer = 2,
   etiq_solicitar = 3,
   etiq_borr_impar = 4,
   etiq_borr_par = 5;


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
void funcion_borrachos( int id )
{
  int valor=0, cervezas=0;
  MPI_Status estado ;
  while ( true )
  {
    cout <<"Borracho " <<id <<" camina hacia la tienda" <<endl ;
    sleep_for( milliseconds( aleatorio<10,100>() ) );
    
    if(id % 2 == 0){
        valor = 2;
        cout << "Borracho " << id << " solicita 2 botellas de cerveza "<<endl;
        MPI_Ssend(&valor,1,MPI_INT,id_dependiente,etiq_borr_par,MPI_COMM_WORLD);
        MPI_Recv(&cervezas,1,MPI_INT,id_dependiente,etiq_borr_par,MPI_COMM_WORLD,&estado);
        cout << "Borracho " << id << " recibe las 2 botellas de cerveza "<<endl;
    }
    else{
        valor = 1;
        cout << "Borracho " << id << " solicita 1 botella de cerveza "<<endl;
        MPI_Ssend(&valor,1,MPI_INT,id_dependiente,etiq_borr_impar,MPI_COMM_WORLD);
        MPI_Recv(&cervezas,1,MPI_INT,id_dependiente,etiq_borr_impar,MPI_COMM_WORLD,&estado);
        cout << "Borracho " << id << " recibe la botella de cerveza "<<endl;
    }

    cout <<"Borracho " <<id <<" bebe como cosaco" <<endl ;
    sleep_for( milliseconds( aleatorio<10,100>() ) );
 }
}

// ---------------------------------------------------------------------
void funcion_cervecero()
{
  int botellas = 15, valor, hay_mens; 
  MPI_Status estado ;                   

  while ( true )
  {
    MPI_Iprobe(id_dependiente,etiq_solicitar,MPI_COMM_WORLD,&hay_mens,&estado);
    if(hay_mens > 0){
        MPI_Recv(&valor,1,MPI_INT,id_dependiente,etiq_solicitar,MPI_COMM_WORLD,&estado);
        cout <<"            Cervecero recibe mensaje del dependiente. Llevando botellas a la tienda" <<endl ;
        sleep_for( milliseconds( aleatorio<10,100>() ) );
        
        MPI_Ssend(&botellas,1,MPI_INT,id_dependiente,etiq_reponer,MPI_COMM_WORLD);
        cout <<"            Cervecero repone las botellas de la tienda" <<endl ;
            
        cout <<"            Cervecero de vuelta a la bodega" <<endl ;
        sleep_for( milliseconds( aleatorio<10,100>() ) );
    }
  }
}

// ---------------------------------------------------------------------
void funcion_dependiente(){
    int botellas = 15, valor, id, etiq_aceptable;
	MPI_Status estado;
        
    // 1º Comprobamos de quien podemos recibir mensajes
    while(true){
        if( botellas >= 2){
            etiq_aceptable = MPI_ANY_TAG;
        }
        else if(botellas == 1){
            etiq_aceptable = etiq_borr_impar;
        }
        else if (botellas == 0){
            etiq_aceptable = etiq_solicitar;
        }
        
        // 2º Recibimos el mensaje del emisor aceptado
        MPI_Recv( &valor, 1, MPI_INT, MPI_ANY_SOURCE, etiq_aceptable, MPI_COMM_WORLD, &estado);
        id = estado.MPI_SOURCE;

        // 3. procesar el mensaje recibido
        switch( estado.MPI_TAG )
        {
            case etiq_borr_par:
                botellas = botellas - 2;
                valor = 2;
                cout <<" ***Dependiente atiende al borracho " << id << " y le sirve " << valor << " cervezas. (" << botellas << " botellas restantes)" <<endl ;
                MPI_Ssend(&valor,1,MPI_INT,id,etiq_borr_par,MPI_COMM_WORLD);
            break;

            case etiq_borr_impar:
                botellas = botellas - 1;
                valor = 1;
                cout <<" ***Dependiente atiende al borracho " << id << " y le sirve " << valor << " cervezas.(" << botellas << " botellas restantes)" <<endl ;
                MPI_Ssend(&valor,1,MPI_INT,id,etiq_borr_impar,MPI_COMM_WORLD);
            break;

            case etiq_solicitar:
                cout <<" ***Dependiente solicita reponer las botellas al cervecero." <<endl ;
                MPI_Ssend(&valor,1,MPI_INT,id_cervecero,etiq_solicitar,MPI_COMM_WORLD);

                MPI_Recv(&valor,1,MPI_INT,id_cervecero,etiq_reponer,MPI_COMM_WORLD,&estado);
                botellas = valor;
                cout <<" ***Dependiente vuelve a tener " << valor << " botellas en la tienda. " <<endl ;

            break; 
        }
    }

}

// ---------------------------------------------------------------------
int main( int argc, char** argv )
{
   int id_propio, num_procesos_actual ;

   MPI_Init( &argc, &argv );
   MPI_Comm_rank( MPI_COMM_WORLD, &id_propio );
   MPI_Comm_size( MPI_COMM_WORLD, &num_procesos_actual );


   if ( num_procesos == num_procesos_actual )
   {
      // ejecutar la función correspondiente a 'id_propio'
      if ( id_propio < num_borrachos )           // si es par
         funcion_borrachos( id_propio );  //   es un filósofo
      else if(id_propio == id_dependiente)         // si es impar
         funcion_dependiente();  //   es un tenedor
      else if(id_propio == id_cervecero)     // si es el camarero
	 funcion_cervecero();
   }
   else
   {
      if ( id_propio == 0 ) // solo el primero escribe error, indep. del rol
      { cout << "el número de procesos esperados es:    " << num_procesos << endl
             << "el número de procesos en ejecución es: " << num_procesos_actual << endl
             << "(programa abortado)" << endl ;
      }
   }

   MPI_Finalize( );
   return 0;
}

// ---------------------------------------------------------------------
