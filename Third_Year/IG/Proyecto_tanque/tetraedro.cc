#include "aux.h"
#include "malla.h"
#include "tetraedro.h"
#include "cmath"

//*****************************************************************************************
// Método que dado el lado, calcula los vertices para crear un tetraedro regular centrado
void Tetraedro::CalculaVertices(float lado){
   //Calculamos la altura del triángulo rectángulo
   float h = (sqrt(3) * lado)/2;

   //Gracias a la altura (h) calculamos valores claves para la creación del tetraedro
   float z1 = (1.0/3.0) * h;              
   float z2 = (2.0/3.0) * h;              
   float y = (1.0/4.0) * h;               // Valor necesario para centrar el tetraedro

   //Inicializamos los 3 primeros vértices que forman la base del tetraedro
  //  Tupla3f v1 = {z1, -y, -lado/2};
  //  Tupla3f v2 = {z1, -y, lado/2};
  //  Tupla3f v3 = {-z2, -y, 0};
   Tupla3f v1 = {z1, -y, -lado/2};
   Tupla3f v2 = {z1, -y, lado/2};
   Tupla3f v3 = {-z2, -y, 0};

   //Calculamos la altura del tetraedro H = sqrt(h² - (1/3*h)²)
   float H = sqrt(pow(h, 2) - pow(z1, 2));
   
   //Añadimos el vértice final
   Tupla3f v4 = {0, H-y, 0};
   v={v1,v2,v3,v4};
}

Tetraedro::Tetraedro()
{ 
   // inicializar la tabla de vértices
   CalculaVertices(100);
   
   // inicializar la tabla de caras o triángulos:
   Tupla3i f1 = {3, 2, 1}; 
   Tupla3i f2 = {1, 2, 0};
   Tupla3i f3 = {1, 0, 3};
   Tupla3i f4 = {3, 0, 2};
   f={f1,f2,f3,f4}; //Añadimos las caras a nuestra tabla

   // inicializamos los tabla de colores del modo sólido
   Tupla3f c_s1 = {0,255,0},c_s2 = {0,255,0},c_s3 = {0,255,0},c_s4 = {0,255,0};
   std::vector<Tupla3f> c_s = {c_s1,c_s2,c_s3,c_s4};
   
   // inicializamos los tabla de colores del modo puntos
   Tupla3f c_p1 = {255,0,0},c_p2 = {255,0,0},c_p3 = {255,0,0},c_p4 = {255,0,0};
   std::vector<Tupla3f> c_p = {c_p1,c_p2,c_p3,c_p4};

   // inicializamos los tabla de colores del modo lineas
   Tupla3f c_l1 = {0,0,255},c_l2 = {0,0,255},c_l3 = {0,0,255},c_l4 = {0,0,255};
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
   this->aj_rojo = {ajd1, ajd1, ajd1, ajd1, ajd1, ajd1, ajd1, ajd1};
   this->aj_verde = {ajd2, ajd2, ajd2, ajd2, ajd2, ajd2, ajd2, ajd2};
   
   calcular_normales();
}

