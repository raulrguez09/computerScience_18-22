#include "aux.h"
#include "objrevolucion.h"
#include "ply_reader.h"
#include "math.h"
using namespace std;


// *****************************************************************************
//
// Clase ObjRevolucion (práctica 2)
//
// *****************************************************************************


// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

ObjRevolucion::ObjRevolucion() {}

ObjRevolucion::ObjRevolucion(const std::string & archivo, int num_instancias, bool textura_act, bool tapa_sup, bool tapa_inf) {
   std::vector<Tupla3f> perfil_original;

   // Obtenemos el perfil original
   ply::read_vertices(archivo, perfil_original);

   tapaSup = tapa_sup;
   tapaInf = tapa_inf;
   texturaActiva = textura_act;

   crearMalla(perfil_original, num_instancias, textura_act, 'y', 0, tapa_sup, tapa_inf);
}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)

ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, bool tapa_sup, bool tapa_inf) {
   tapaSup = tapa_sup;
   tapaInf = tapa_inf;

   crearMalla(archivo, num_instancias, true, 'y',0, tapa_sup, tapa_inf);
}

// *****************************************************************************
// Función para cambiar el eje donde se crea la malla

Tupla3f ObjRevolucion::rotacionEje(std::vector<Tupla3f> perfil_original, char eje, int j, float coseno, float seno){
   float px, py, pz;
   Tupla3f vertice;
   switch (eje) {
      case 'y':
         // Rotación en y
         px = coseno*perfil_original[j](0) + seno*perfil_original[j](2);
         py = perfil_original[j](1);
         pz = -seno*perfil_original[j](0) + coseno*perfil_original[j](2);

         break;
      case 'x':
         // Rotación en x
         px = perfil_original[j](0);
         py = coseno*perfil_original[j](1) - seno*perfil_original[j](2);
         pz = seno*perfil_original[j](1) + coseno*perfil_original[j](2);

         break;
      case 'z':
         // Rotación en Z
         px = coseno*perfil_original[j](0) - seno*perfil_original[j](1);
         py = seno*perfil_original[j](0) + coseno*perfil_original[j](1);
         pz = perfil_original[j](2);
         break;
   }

   vertice={px,py,pz};
   return vertice;
}

// *****************************************************************************
// Función que crea la malla a partir del perfil

void ObjRevolucion::crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias, bool textura_act, char eje, int color, bool tapa_sup, bool tapa_inf) {
   if(textura_act){
      texturaActiva = true;
   }
   else{
      texturaActiva = false;
   }
   
   const float PI = atan(1) * 4;
   int a, b, num_ver_perf = perfil_original.size();
   float angulo, cos_ang, sin_ang, px, py, pz;
   Tupla3f vertice, poloSur, poloNorte;
   Tupla3i caraCreada;
   bool ascendente;

   // Comprobar si los vertices estan en orden ascendente o descendente
   switch(eje){
      case 'x':
         ascendente = perfil_original.front()(0) < perfil_original.back()(0);
      break;

      case 'y':
         ascendente = perfil_original.front()(1) < perfil_original.back()(1);
      break;

      case 'z':
         ascendente = perfil_original.front()(2) < perfil_original.back()(2);
      break;
   }
   
   // Invertimos el vector si no es ascendente
   if (!ascendente) {
      std::vector<Tupla3f> original (perfil_original.rbegin(), perfil_original.rend());
      perfil_original = original;
   }

   // Comprobar si hay polo sur 
      switch(eje){
         case 'x':
            if(fabs(perfil_original.front()(1)) < std::numeric_limits<float>::epsilon() && 
               fabs(perfil_original.front()(2)) < std::numeric_limits<float>::epsilon()){
               poloSur = perfil_original.front();
               perfil_original.erase(perfil_original.begin());
            }else{
               poloSur(0) = perfil_original.front()(0);
               poloSur(1) = 0.0;
               poloSur(2) = 0.0;
            }
         break;
         case 'y':
            if(fabs(perfil_original.front()(0)) < std::numeric_limits<float>::epsilon() && 
               fabs(perfil_original.front()(2)) < std::numeric_limits<float>::epsilon()){
               poloSur = perfil_original.front();
               perfil_original.erase(perfil_original.begin());
            }else{         
               poloSur(0) = 0.0;
               poloSur(1) = perfil_original.front()(1);
               poloSur(2) = 0.0;
            }
         break;
         case 'z':
            if(fabs(perfil_original.front()(0)) < std::numeric_limits<float>::epsilon() && 
               fabs(perfil_original.front()(1)) < std::numeric_limits<float>::epsilon()){
               poloSur = perfil_original.front();
               perfil_original.erase(perfil_original.begin());
            }else{
               poloSur(0) = 0.0;
               poloSur(1) = 0.0;
               poloSur(2) = perfil_original.front()(2); 
            }    
         break;
      }

   // Comprobar si hay polo norte
      switch(eje){
         case 'x':
            if(fabs(perfil_original.back()(1)) < std::numeric_limits<float>::epsilon() && 
               fabs(perfil_original.back()(2)) < std::numeric_limits<float>::epsilon()){
               poloNorte = perfil_original.back(); 
               perfil_original.pop_back();
            }else{      
               poloNorte(0) = perfil_original.back()(0);
               poloNorte(1) = 0.0,
               poloNorte(2) = 0.0;
            }
         break;
         case 'y':
            if(fabs(perfil_original.back()(0)) < std::numeric_limits<float>::epsilon() && 
               fabs(perfil_original.back()(2)) < std::numeric_limits<float>::epsilon()){
               poloNorte = perfil_original.back();   
               perfil_original.pop_back();
            }else{       
               poloNorte(0) = 0.0;
               poloNorte(1) = perfil_original.back()(1);
               poloNorte(2) = 0.0;
            }
         break;
         case 'z':
            if(fabs(perfil_original.back()(0)) < std::numeric_limits<float>::epsilon() && 
               fabs(perfil_original.back()(1)) < std::numeric_limits<float>::epsilon()){
               poloNorte = perfil_original.back();    
               perfil_original.pop_back();
            }else{      
               poloNorte(0) = 0.0;
               poloNorte(1) = 0.0,
               poloNorte(2) = perfil_original.back()(2); 
            }     
         break;
      }

   v.clear();
   f.clear();

   num_ver_perf = perfil_original.size();

   // Creamos la tabla de vértices
   for(int i = 0; i <= num_instancias - 1; i++){
      angulo = (2*PI*i)/num_instancias;
      cos_ang = cos(angulo);
      sin_ang = sin(angulo);
      for(int j = 0; j <= num_ver_perf - 1; j++){
         vertice = rotacionEje(perfil_original, eje, j, cos_ang, sin_ang);
         this->v.push_back(vertice);
      }
   }

   if(texturaActiva){
      num_instancias++;
      for(int i = 0; i < perfil_original.size(); i++){
         v.push_back(perfil_original[i]);
      }
   }
   
   // Creamos la tabla de triángulos
   int numero_ins = num_instancias;
   if(texturaActiva){
      numero_ins = num_instancias-1;
   }

   for(int i = 0; i < numero_ins; i++){
      // if(texturaActiva && num_instancias < num_instancias-1)
      // continue;
      for(int j = 0; j <= num_ver_perf - 2; j++){
         a =  num_ver_perf*i + j;
         b = num_ver_perf*((i + 1) % num_instancias) + j;
         this->f.push_back({a, b, b+1});
         this->f.push_back({a, b+1, a+1});
      }
   }

   if(tapa_inf){
      // Insertamos el polo sur
      v.push_back(poloSur);

      // Creamos las caras de la tapa sur
      for (int i=0; i<num_instancias; i++) {
         int v2 = num_ver_perf*((i+1) % num_instancias);
         int v3 = i*num_ver_perf;

         caraCreada = {(int)v.size()-1, v2, v3};
         f.insert(f.begin(), caraCreada);
         //f.push_back(caraCreada);
      }
   }

   if(tapa_sup){
      // Insertamos el polo norte
      v.push_back(poloNorte);

      // Creamos las caras de la tapa norte
      for (int i=0; i<num_instancias; i++){
         int v2 = (num_ver_perf*i + num_ver_perf-1) % (num_instancias*num_ver_perf);
         int v3 = (num_ver_perf*((i+1) % num_instancias) + num_ver_perf-1) % (num_instancias*num_ver_perf);
         
         caraCreada = {num_ver_perf*num_instancias+1, v2 ,  v3};
         f.insert(f.begin(), caraCreada);
         f.push_back(caraCreada);
      }
   }


   instancias = num_instancias;

   Tupla3f verde = {0,255,0}, rojo = {255, 0, 0}, azul = {0,0,255};
   std::vector<Tupla3f> c_s, c_p, c_l;
   
   for(int i = 0; i < this->v.size(); i++){
      if(color == 1){
         c_s.push_back(verde);
      }
      else{
         c_s.push_back(azul); 
      }
      c_p.push_back(verde); 
      c_l.push_back(rojo); 
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

   //setColoresSeleccion({1,1,1});
   calcularCentroObjeto();
   calcular_normales();
   
   if(texturaActiva){
      crearTextura(perfil_original, num_instancias);
   }

}

// *****************************************************************************
// Función que crear las coordenadas de texturas
void ObjRevolucion::crearTextura(std::vector<Tupla3f> perfil_original, int num_instancias){
   float N = num_instancias;
   float M = perfil_original.size();
   std::vector<float> distancias;
   float s, t;

   distancias.resize(M);
   distancias[0] = 0;
   Tupla3f resta;

   for(int i = 1; i < M; i++){
      resta = v[i] - v[i-1];
      distancias[i] = distancias[i-1] + sqrt(pow(resta(0),2) + pow(resta(1),2) + pow(resta(2), 2));
   }

   ct.resize(v.size());
   for(int i = 0; i < N; i++){
      s = i/(N-1);
      for(int j = 0; j < M; j++){
         t = distancias[j]/distancias[M-1];
         ct[(M*i)+j] = {s,t};
      }
   }
}

// *****************************************************************************
// Funciones para dibujar los objetosRevolucion

// -----------------------------------------------------------------------------
//Función para crear los VBO
GLuint  CrearVBOrev( GLuint  tipo_vbo , GLuint  tamanio_bytes ,GLvoid * puntero_ram ){
   GLuint  id_vbo ;                       // resultado: identificador de VBO
   glGenBuffers( 1, & id_vbo  );          // crear nuevo VBO, obtener identificador(nunca 0)
   glBindBuffer( tipo_vbo , id_vbo  );    // activar el VBO usando su identificador
   
   // esta instrucción hace la transferencia de datos desde RAM hacia GPU
   glBufferData( tipo_vbo , tamanio_bytes , puntero_ram , GL_STATIC_DRAW  );
   glBindBuffer( tipo_vbo , 0 );          // desactivación del VBO (activar 0)
   
   return  id_vbo ;                       // devolver el identificador resultado
}

// -----------------------------------------------------------------------------
// Visualización en modo inmediato con 'glDrawElements'
void ObjRevolucion::draw_ModoInmediato(bool ajedrez, unsigned int color, bool modoLuz, bool tapaSup, bool tapaInf)
{        
      // habilitar uso de un array de vértices 
      glEnableClientState( GL_VERTEX_ARRAY );
      
      // indicar el formato y la dirección de memoria del array de vértices
      // (son tuplas de 3 valoresfloat, sin espacio entre ellas)
      glVertexPointer( 3, GL_FLOAT , 0, v.data() );
      
      if (textura != nullptr) {
         glEnableClientState(GL_TEXTURE_COORD_ARRAY);
         glTexCoordPointer(2, GL_FLOAT, 0, ct.data());
         textura->activar();
      }

      if(modoLuz){
         glEnableClientState( GL_NORMAL_ARRAY );
         glNormalPointer( GL_FLOAT, 0, n_vert.data());
         m.aplicar();
      }else{
         glEnableClientState( GL_COLOR_ARRAY ); // habilitar uso de array de col.

         if(ajedrez){
            glColorPointer(3, GL_FLOAT, 0, aj_verde.data());    // especifíca puntero a colores 
            glDrawElements( GL_TRIANGLES , pares.size ()*3,GL_UNSIGNED_INT , pares.data() );

            glColorPointer(3, GL_FLOAT, 0, aj_rojo.data());    // especifíca puntero a colores 
            glDrawElements( GL_TRIANGLES , impares.size ()*3,GL_UNSIGNED_INT , impares.data() );
         }
         else{
            if(color == 3){
               glColorPointer(3,GL_FLOAT,0,coloresSeleccion.data());
            }
            else{
               glColorPointer( 3, GL_FLOAT, 0, colores[color].data()); // especifíca puntero a colores
            }
         }
      }
         // visualizar, indicando: tipo de primitiva, número de índices,
         // tipo de los índices, y dirección de la tabla de índices
         if(!tapaInf && !tapaSup){
            glDrawElements( GL_TRIANGLES , (f.size()-2*instancias)*3, GL_UNSIGNED_INT , f.data()+2*instancias);
         }
         else if(!tapaInf && tapaSup){
            glDrawElements( GL_TRIANGLES , (f.size()-instancias)*3, GL_UNSIGNED_INT , f.data()+instancias);
         }
         else if (tapaSup && tapaInf){
            glDrawElements( GL_TRIANGLES , f.size()*3, GL_UNSIGNED_INT , f.data());            
         }
      
      // deshabilitar array de vértices
      glDisableClientState( GL_VERTEX_ARRAY );

      if(modoLuz){
         glDisableClientState( GL_NORMAL_ARRAY );
      }
      else{
         // deshabilitar array de colores
         glDisableClientState( GL_COLOR_ARRAY );
      }

      if (textura != nullptr) {
         glDisableClientState( GL_TEXTURE_COORD_ARRAY );
         glDisable(GL_TEXTURE_2D);
      }
}

// -----------------------------------------------------------------------------
//Visualización en modo diferido con 'glDrawElements' (usando VBOs)
void ObjRevolucion::draw_ModoDiferido(bool ajedrez, unsigned int color, bool modoLuz, bool tapaSup, bool tapaInf)
{
   // Primero comprobamos el buffer de vertices
   if(id_vbo_ver == 0){
      id_vbo_ver = CrearVBOrev(GL_ARRAY_BUFFER, v.size()*sizeof(Tupla3f), v.data());
   }

   glBindBuffer( GL_ARRAY_BUFFER, id_vbo_ver );       // activar VBO de vértices
   glVertexPointer( 3, GL_FLOAT, 0, 0 );              // especifica formato y offset (=0)
   glBindBuffer( GL_ARRAY_BUFFER, 0 );                // desactivar VBO de vértices.
   glEnableClientState( GL_VERTEX_ARRAY );            // habilitar tabla de vértices

   if(ajedrez){
      if(id_vbo_par == 0){
         id_vbo_par = CrearVBOrev(GL_ELEMENT_ARRAY_BUFFER, pares.size()*sizeof(Tupla3f), pares.data());
      }

      if(id_vbo_impar == 0){
         id_vbo_impar = CrearVBOrev(GL_ELEMENT_ARRAY_BUFFER, impares.size()*sizeof(Tupla3f), impares.data());
      }

      if(id_vbo_verde == 0){
         id_vbo_verde = CrearVBOrev(GL_ARRAY_BUFFER, aj_verde.size()*sizeof(Tupla3f), aj_verde.data());
      }

      if(id_vbo_rojo == 0){
         id_vbo_rojo = CrearVBOrev(GL_ARRAY_BUFFER, aj_rojo.size()*sizeof(Tupla3f), aj_rojo.data());
      }

      glBindBuffer(GL_ARRAY_BUFFER, id_vbo_verde); // activar VBO de colores
      glColorPointer (3, GL_FLOAT, 0, 0); 
      glBindBuffer( GL_ARRAY_BUFFER, 0 ); // desactivar VBO de colores
      glEnableClientState( GL_COLOR_ARRAY ); // habilitar la tabla de colores

      glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, id_vbo_par );// activar VBO de triángulos
      glDrawElements( GL_TRIANGLES, 3*pares.size(), GL_UNSIGNED_INT, 0 ) ;
      glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 ); //desactivar VBO de triangulos
   
      glDisableClientState(GL_ARRAY_BUFFER);
   
      glBindBuffer(GL_ARRAY_BUFFER, id_vbo_rojo); // activar VBO de colores
      glColorPointer (3, GL_FLOAT, 0, 0); 
      glBindBuffer( GL_ARRAY_BUFFER, 0 ); // desactivar VBO de colores
      glEnableClientState( GL_COLOR_ARRAY ); // habilitar la tabla de colores

      glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, id_vbo_impar );// activar VBO de triángulos
      glDrawElements( GL_TRIANGLES, 3*impares.size(), GL_UNSIGNED_INT, 0 ) ;
      glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 ); //desactivar VBO de triangulos

      // desactivar uso de array de vértices y colores
      glDisableClientState( GL_VERTEX_ARRAY );
      glDisableClientState(GL_ARRAY_BUFFER);
   }
   else{

      // Ahora comprobamos el buffer de colores
      id_vbo_col = CrearVBOrev(GL_ARRAY_BUFFER, colores[color].size()*sizeof(Tupla3f), colores[color].data());

      if(!tapaInf && !tapaSup){
         id_vbo_tri = CrearVBOrev(GL_ELEMENT_ARRAY_BUFFER, (f.size()-2*instancias)*sizeof(Tupla3i), f.data()+2*instancias);
      }
      else if(!tapaInf){
         id_vbo_tri = CrearVBOrev(GL_ELEMENT_ARRAY_BUFFER, (f.size()-3*instancias)*sizeof(Tupla3i), f.data()+3*instancias);
      }
      else if (tapaSup && tapaInf){
         id_vbo_tri = CrearVBOrev(GL_ELEMENT_ARRAY_BUFFER, f.size()*sizeof(Tupla3i), f.data());
      }

         glBindBuffer(GL_ARRAY_BUFFER, id_vbo_col); // activar VBO de colores
         glColorPointer (3, GL_FLOAT, 0, 0); 
         glBindBuffer( GL_ARRAY_BUFFER, 0 ); // desactivar VBO de colores
         glEnableClientState( GL_COLOR_ARRAY ); // habilitar la tabla de colores

         glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri);// activar VBO de triángulos
         glDrawElements( GL_TRIANGLES, 3*f.size(), GL_UNSIGNED_INT, 0 ) ;
         glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 ); //desactivar VBO de triangulos
      
         // desactivar uso de array de vértices y colores
         glDisableClientState( GL_VERTEX_ARRAY );
         glDisableClientState(GL_ARRAY_BUFFER);
   }
}

// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido
void ObjRevolucion::draw(unsigned int modo, bool modoLuz, unsigned int color,  bool ajedrez, bool tapaSup, bool tapaInf)
{
      switch(modo){
         case 0:
            draw_ModoInmediato(ajedrez, color, modoLuz, tapaSup, tapaInf);
            break;

         case 1:
            draw_ModoDiferido(ajedrez, color, modoLuz, tapaSup, tapaInf);
            break;
      }
}