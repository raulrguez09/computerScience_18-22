#include "aux.h"
#include "malla.h"
#include "cubo.h"
 
Cubo::Cubo(float lado){
   // inicializar la tabla de vértices
   Tupla3f v1 = {-lado/2, -lado/2, lado/2}; // - - + 
   Tupla3f v2 = {lado/2, -lado/2, lado/2};  // + - + 
   Tupla3f v3 = {lado/2, -lado/2, -lado/2}; // + - - 
   Tupla3f v4 = {-lado/2, -lado/2, -lado/2}; // - - -  
   Tupla3f v5 = {-lado/2, lado/2, lado/2};  // - + + 
   Tupla3f v6 = {lado/2, lado/2, lado/2};   // + + + 
   Tupla3f v7 = {lado/2, lado/2, -lado/2};  // + + - 
   Tupla3f v8 = {-lado/2, lado/2, -lado/2};// - + - 
   v={v1,v2,v3,v4,v5,v6,v7,v8};

   // inicializar la tabla de caras o triángulos:
   Tupla3i f1 = {0,1,4}, f2 = {4,1,5}, f3 = {2,5,1}, f4 = {6,5,2}, f5 = {4,5,6}, f6 = {4,6,7},
           f7 = {2,1,0}, f8 = {2,0,3}, f9 = {4,3,0}, f10 = {4,7,3}, f11 = {3,7,2}, f12 = {2,7,6}; 
   f={f1,f2,f3,f4,f5,f6,f7,f8,f9,f10,f11,f12};

   // inicializamos los tabla de colores del modo sólido
   Tupla3f c_s1 = {255,0,0}, c_s2 = {255,0,0}, c_s3 = {255,0,0}, c_s4 = {255,0,0},
           c_s5 = {255,0,0}, c_s6 = {255,0,0}, c_s7 = {255,0,0}, c_s8 = {255,0,0};
   std::vector<Tupla3f> c_s = {c_s1,c_s2,c_s3,c_s4,c_s5,c_s6,c_s7,c_s8};
   
   // inicializamos los tabla de colores del modo puntos
   Tupla3f c_p1 = {0,255,0}, c_p2 = {0,255,0}, c_p3 = {0,255,0}, c_p4 = {0,255,0},
           c_p5 = {0,255,0}, c_p6 = {0,255,0}, c_p7 = {0,255,0}, c_p8 = {0,255,0};
   std::vector<Tupla3f> c_p = {c_p1,c_p2,c_p3,c_p4,c_p5,c_p6,c_p7,c_p8};

   // inicializamos los tabla de colores del modo lineas
   Tupla3f c_l1 = {0,0,255}, c_l2 = {0,0,255}, c_l3 = {0,0,255}, c_l4 = {0,0,255},
           c_l5 = {0,0,255}, c_l6 = {0,0,255}, c_l7 = {0,0,255}, c_l8 = {0,0,255};
   std::vector<Tupla3f> c_l = {c_l1,c_l2,c_l3,c_l4,c_l5,c_l6,c_l7,c_l8};

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
   this->aj_rojo = {ajd1, ajd1, ajd1, ajd1, ajd1, ajd1, ajd1, ajd1};
   this->aj_verde = {ajd2, ajd2, ajd2, ajd2, ajd2, ajd2, ajd2, ajd2};

   calcular_normales();
}

