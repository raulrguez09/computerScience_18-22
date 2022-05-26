#include "objply.h"
#include "ply_reader.h"
 

// *****************************************************************************
//
// Clase ObjPLY (práctica 2)
//
// *****************************************************************************

ObjPLY::ObjPLY( const std::string & nombre_archivo )
{
   // leer la lista de caras y vértices
   ply::read(nombre_archivo, this->v, this->f );

   //Inicializamos las tablas de colores para el modo solido, punto y linea
   Tupla3f verde = {0,255,0}, rojo = {255, 0, 0}, azul = {0,0,255};
   std::vector<Tupla3f> c_s, c_p, c_l;
   
   for(int i = 0; i < this->v.size(); i++){
      c_s.push_back(rojo); 
      c_p.push_back(verde); 
      c_l.push_back(azul); 
   }
   colores = {c_s, c_p, c_l};

   //Inicializamos las tablas de colores para el modo ajedrez
   pares.reserve(this->f.size()/2);
   impares.reserve(this->f.size()/2);

   for(int i = 0; i < this->f.size(); i++){
     if(i%2 == 0){
       pares.push_back(this->f[i]);
     }
     else{
       impares.push_back(this->f[i]);
     }
   }

   this->aj_rojo = c_s;
   this->aj_verde = c_p;
   
}


