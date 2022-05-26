// -----------------------------------------------------------------------------
// Sistemas concurrentes y Distribuidos.
// Práctica 3. Implementación de algoritmos distribuidos con MPI
//
// Archivo: filosofos-cam.cpp
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
   num_filosofos = 5 ,
   num_procesos  = 2*num_filosofos +1,
   etiq_sentarse = 0 , 
   etiq_levantarse = 1 ,
   id_camarero = 10,
   // Examen -----
   id_malafolla = 6,
   etiq_sillas = 2;


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
void funcion_filosofos( int id )
{
  int id_ten_izq = (id+1)              % (num_procesos-1), //id. tenedor izq.
      id_ten_der = (id+num_procesos-1-1) % (num_procesos-1), //id. tenedor der.
      valor=id,
      sillas=0;
    MPI_Status estado ;       // metadatos de las dos recepciones


  while ( true )
  {
    if(id != 6){    
        cout << "Filósofo " << id << " solicita sentarse en la mesa "<<endl;

        // Solicitamos sentarnos en la mesa antes de solicitar los tenedores
        MPI_Ssend(&valor,1,MPI_INT,id_camarero,etiq_sentarse,MPI_COMM_WORLD);
        //-------------------------------------------------------------------

        cout <<"Filósofo " <<id << " solicita ten. izq." <<id_ten_izq <<endl;
        MPI_Ssend(&valor,1,MPI_INT,id_ten_izq,0,MPI_COMM_WORLD);       // solicitar tenedor izd

        cout <<"Filósofo " <<id <<" solicita ten. der." <<id_ten_der <<endl;
        MPI_Ssend(&valor,1,MPI_INT,id_ten_der,0,MPI_COMM_WORLD);       // solicitar tenedor dch

        cout <<"Filósofo " <<id <<" comienza a comer" <<endl ;
        sleep_for( milliseconds( aleatorio<10,100>() ) );

        cout <<"Filósofo " <<id <<" suelta ten. izq. " <<id_ten_izq <<endl;
        MPI_Ssend(&valor,1,MPI_INT,id_ten_izq,0,MPI_COMM_WORLD);       // soltar tenedor izd

        cout<< "Filósofo " <<id <<" suelta ten. der. " <<id_ten_der <<endl;
        MPI_Ssend(&valor,1,MPI_INT,id_ten_der,0,MPI_COMM_WORLD);       // soltar tenedor dch

        cout << "Filósofo " << id << " solicita levantarse " << endl;
        // Solicitamos levantarnos de la mesa antes de pensar
        MPI_Ssend(&valor,1,MPI_INT,id_camarero,etiq_levantarse,MPI_COMM_WORLD);
        //-------------------------------------------------------------------

        cout << "Filosofo " << id << " comienza a pensar" << endl;
        sleep_for( milliseconds( aleatorio<10,100>() ) );
    }
    else{
        cout << "***Filósofo " << id << " (malafollá) solicita sentarse en la mesa "<<endl;

        // Solicitamos sentarnos en la mesa antes de solicitar los tenedores
        MPI_Ssend(&valor,1,MPI_INT,id_camarero,etiq_sentarse,MPI_COMM_WORLD);
        MPI_Recv(&sillas,1,MPI_INT,id_camarero,etiq_sillas,MPI_COMM_WORLD,&estado);
        
        if(sillas == 1){
            cout << "***Malditos comilones, levantaros ya de la mesa" << endl;
        }

        //-------------------------------------------------------------------
        
        cout <<"Filósofo " <<id << " (malafollá) solicita ten. izq." <<id_ten_izq <<endl;
        MPI_Ssend(&valor,1,MPI_INT,id_ten_izq,0,MPI_COMM_WORLD);       // solicitar tenedor izd

        cout <<"Filósofo " <<id <<" (malafollá) solicita ten. der." <<id_ten_der <<endl;
        MPI_Ssend(&valor,1,MPI_INT,id_ten_der,0,MPI_COMM_WORLD);       // solicitar tenedor dch

        cout <<"Filósofo " <<id <<" (malafollá) comienza a comer" <<endl ;
        sleep_for( milliseconds( aleatorio<10,100>() ) );

        cout <<"Filósofo " <<id <<" (malafollá) suelta ten. izq. " <<id_ten_izq <<endl;
        MPI_Ssend(&valor,1,MPI_INT,id_ten_izq,0,MPI_COMM_WORLD);       // soltar tenedor izd

        cout<< "Filósofo " <<id <<" (malafollá) suelta ten. der. " <<id_ten_der <<endl;
        MPI_Ssend(&valor,1,MPI_INT,id_ten_der,0,MPI_COMM_WORLD);       // soltar tenedor dch
        
        cout << "Filósofo " << id << " (malafollá) solicita levantarse " << endl;
        // Solicitamos levantarnos de la mesa antes de pensar
        MPI_Ssend(&valor,1,MPI_INT,id_camarero,etiq_levantarse,MPI_COMM_WORLD);
        //-------------------------------------------------------------------

        cout << "Filosofo " << id << " (malafollá) comienza a pensar" << endl;
        sleep_for( milliseconds( aleatorio<10,100>() ) );
    }
 }
}

// ---------------------------------------------------------------------
void funcion_tenedores( int id )
{
  int valor, id_filosofo ;  // valor recibido, identificador del filósofo
  MPI_Status estado ;       // metadatos de las dos recepciones

  while ( true )
  {
     // recibir petición de cualquier filósofo 
     MPI_Recv(&valor,1,MPI_INT,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,&estado);
     // guardar en 'id_filosofo' el id. del emisor 
     id_filosofo = estado.MPI_SOURCE;

     cout <<"     Ten. " <<id <<" ha sido cogido por filo. " <<id_filosofo <<endl;

     // recibir liberación de filósofo 'id_filosofo' 
     MPI_Recv(&valor,1,MPI_INT,id_filosofo,MPI_ANY_TAG,MPI_COMM_WORLD,&estado);

     cout <<"     Ten. "<<id<< " ha sido liberado por filo. " <<id_filosofo <<endl ;
  }
}

// ---------------------------------------------------------------------
void funcion_camarero(){
   int valor, id_filosofo, s=0, hay_mens, sillas;
	MPI_Status estado;

   while(true){

      if(s < (num_filosofos-1)){ //recibir petición de sentarse
         MPI_Recv(&valor,1,MPI_INT,MPI_ANY_SOURCE,etiq_sentarse,MPI_COMM_WORLD,&estado);
         id_filosofo = estado.MPI_SOURCE;
         if(id_filosofo == 6){ // Si es el malafollá
            sillas = s;
            if((sillas + 2) <= 4){
                s = s + 2;
                sillas = 2;
                MPI_Ssend(&sillas,1,MPI_INT,id_filosofo,etiq_sillas,MPI_COMM_WORLD);
                cout << "           Camarero sienta en la mesa a filósofo malafollá " << id_filosofo << " (" << s << " en mesa)" << endl;
            }
            else{
                s++;
                sillas = 1;
                MPI_Ssend(&sillas,1,MPI_INT,id_filosofo,etiq_sillas,MPI_COMM_WORLD);
                cout << "           Camarero sienta en la mesa a filósofo malafollá " << id_filosofo << " (" << s << " en mesa)" << endl;
            }
         }
         else{
            s++;
            cout << "           Camarero sienta en la mesa a filósofo " << id_filosofo << " (" << s << " en mesa)" << endl;
         } 
      }

      MPI_Iprobe(MPI_ANY_SOURCE,etiq_levantarse,MPI_COMM_WORLD,&hay_mens,&estado);
      if(hay_mens > 0){	//permitir levantarse si alguien lo solicita
         id_filosofo = estado.MPI_SOURCE;
         MPI_Recv(&valor,1,MPI_INT,id_filosofo,etiq_levantarse,MPI_COMM_WORLD,&estado);
         if(s == 4){
            s--;
            cout << "           Estaban 4 filósofos sentados y se ha levantado el filósofo " << id_filosofo<< " (" << s << " en mesa)" << endl;  
         }else{
            s--;
            cout << "           Camarero levanta de la mesa a filósofo " << id_filosofo<< " (" << s << " en mesa)" << endl;
         }  
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
      if ( id_propio % 2 == 0 && id_propio < 10 )           // si es par
         funcion_filosofos( id_propio );  //   es un filósofo
      else if(id_propio % 2 != 0)         // si es impar
         funcion_tenedores( id_propio );  //   es un tenedor
      else if(id_propio == id_camarero)     // si es el camarero
		   funcion_camarero();
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
