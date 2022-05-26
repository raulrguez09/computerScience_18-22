#include "aux.h"
#include "malla.h"
#include "cuadro.h"
 
Cuadro::Cuadro(float lado){
   // inicializar la tabla de vértices
   Tupla3f v1 = {0, 0, 0};  
   Tupla3f v2 = {0, lado, 0};   
   Tupla3f v3 = {lado, 0, 0}; 
   Tupla3f v4 = {lado, lado, 0}; 
   v={v1,v2,v3,v4};

   // inicializar la tabla de caras o triángulos:
   Tupla3i f1 = {2,1,0}, f2 = {2,3,1}; 
   f={f1,f2};

   // inicializamos los tabla de colores del modo sólido
   Tupla3f c_s1 = {1.0,1.0,1.0}, c_s2 = {1.0,1.0,1.0}, c_s3 = {1.0,1.0,1.0}, c_s4 = {1.0,1.0,1.0};
   std::vector<Tupla3f> c_s = {c_s1,c_s2,c_s3,c_s4};
   
   // inicializamos los tabla de colores del modo puntos
   Tupla3f c_p1 = {0,255,0}, c_p2 = {0,255,0}, c_p3 = {0,255,0}, c_p4 = {0,255,0};
   std::vector<Tupla3f> c_p = {c_p1,c_p2,c_p3,c_p4};

   // inicializamos los tabla de colores del modo lineas
   Tupla3f c_l1 = {0,0,255}, c_l2 = {0,0,255}, c_l3 = {0,0,255}, c_l4 = {0,0,255};
   std::vector<Tupla3f> c_l = {c_l1,c_l2,c_l3,c_l4};

   //Añadimos todos los colores a nuestro vector de vectores de colores
   colores = {c_s, c_p, c_l};

   // inicializamos los tabla de caras y colores del modo ajedrez 
   pares.reserve(f.size()/2);
   impares.reserve(f.size()/2);

   for(int i = 0; i < f.size(); i++){
     if(i%2 == 0){
       pares.push_back(f[i]);
     }
     else{
       impares.push_back(f[i]);
     }
   }

   Tupla3f ajd1 = {255,0,0}, ajd2 = {0,255,0};
   this->aj_rojo = {ajd1, ajd1, ajd1, ajd1};
   this->aj_verde = {ajd2, ajd2, ajd2, ajd2};

   calcular_normales();
    
   Tupla2f ct1({0,0}), ct2({0,1}), ct3({1,0}), ct4({1,1});
   ct = {ct1, ct2, ct3, ct4};   
}