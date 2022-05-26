#include "aux.h"
#include "malla.h"
using namespace std;

// *****************************************************************************
//
// Clase Malla3D
//
// *****************************************************************************


// -----------------------------------------------------------------------------
//Función para crear los VBO
GLuint  CrearVBO( GLuint  tipo_vbo , GLuint  tamanio_bytes ,GLvoid * puntero_ram ){
   GLuint id_vbo;                       // resultado: identificador de VBO
   glGenBuffers(1, &id_vbo);          // crear nuevo VBO, obtener identificador(nunca 0)
   glBindBuffer(tipo_vbo, id_vbo);    // activar el VBO usando su identificador
   
   // esta instrucción hace la transferencia de datos desde RAM hacia GPU
   glBufferData(tipo_vbo, tamanio_bytes, puntero_ram, GL_STATIC_DRAW);
   glBindBuffer(tipo_vbo, 0);          // desactivación del VBO (activar 0)
   
   return  id_vbo ;                       // devolver el identificador resultado
}

// -----------------------------------------------------------------------------
// Visualización en modo inmediato con 'glDrawElements'
void Malla3D::draw_ModoInmediato(bool ajedrez, unsigned int color, bool modoLuz)
{            
      // habilitar uso de un array de vértices 
      glEnableClientState( GL_VERTEX_ARRAY );
      
      // indicar el formato y la dirección de memoria del array de vértices
      // (son tuplas de 3 valoresfloat, sin espacio entre ellas)
      glVertexPointer( 3, GL_FLOAT , 0, v.data() );
      
      if (ct.size() != 0) {
         glEnableClientState(GL_TEXTURE_COORD_ARRAY);
         glTexCoordPointer(2, GL_FLOAT, 0, ct.data());
         //glEnable(GL_TEXTURE_2D);
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
      glDrawElements( GL_TRIANGLES , f.size ()*3,GL_UNSIGNED_INT , f.data() );
      
      // deshabilitar array de vértices
      glDisableClientState( GL_VERTEX_ARRAY );

      if(modoLuz){
         glDisableClientState( GL_NORMAL_ARRAY );
      }
      else{
         // deshabilitar array de colores
         glDisableClientState( GL_COLOR_ARRAY );
      }

      if (ct.size() != 0) {
         glDisableClientState( GL_TEXTURE_COORD_ARRAY );
         glDisable(GL_TEXTURE_2D);
      }
}
 
// -----------------------------------------------------------------------------
//Visualización en modo diferido con 'glDrawElements' (usando VBOs)
void Malla3D::draw_ModoDiferido(bool ajedrez, unsigned int color, bool modoLuz)
{
   // Primero comprobamos el buffer de vertices
   if(id_vbo_ver == 0){
      id_vbo_ver = CrearVBO(GL_ARRAY_BUFFER, v.size()*sizeof(Tupla3f), v.data());
   }

   if(id_vbo_nv==0 && glIsEnabled(GL_LIGHTING))
        id_vbo_nv=CrearVBO(GL_ARRAY_BUFFER,n_vert.size()*sizeof(float)*3,n_vert.data());

   if(id_vbo_ct==0 && textura != nullptr)
        id_vbo_ct=CrearVBO(GL_ARRAY_BUFFER,ct.size()*sizeof(float)*2,ct.data());
    

   if(!ajedrez){
        switch (color){
        case 0:
            if(id_vbo_col==0) id_vbo_col=CrearVBO(GL_ARRAY_BUFFER,colores[color].size()*sizeof(float)*3,colores[color].data());     // Color solido por defecto
            break;
        case 1:
            if(id_vbo_col==0) id_vbo_col =CrearVBO(GL_ARRAY_BUFFER,colores[color].size()*sizeof(float)*3,colores[color].data());    // Color para puntos
            break;
        case 2:
            if(id_vbo_col==0) id_vbo_col=CrearVBO(GL_ARRAY_BUFFER,colores[color].size()*sizeof(float)*3,colores[color].data());     // Color para lineas
            break;
        case 3:
            if(id_vbo_coloresSeleccion==0) id_vbo_coloresSeleccion=CrearVBO(GL_ARRAY_BUFFER,coloresSeleccion.size()*sizeof(float)*3,coloresSeleccion.data()); 
         break;
        }

        if(id_vbo_tri==0) id_vbo_tri=CrearVBO(GL_ELEMENT_ARRAY_BUFFER,f.size()*sizeof(int)*3,f.data()); // Triangulos        
   }
   else{
      if(id_vbo_par == 0){
         id_vbo_par = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, pares.size()*sizeof(Tupla3f), pares.data());
      }

      if(id_vbo_impar == 0){
         id_vbo_impar = CrearVBO(GL_ELEMENT_ARRAY_BUFFER, impares.size()*sizeof(Tupla3f), impares.data());
      }

      if(id_vbo_verde == 0){
         id_vbo_verde = CrearVBO(GL_ARRAY_BUFFER, aj_verde.size()*sizeof(Tupla3f), aj_verde.data());
      }

      if(id_vbo_rojo == 0){
         id_vbo_rojo = CrearVBO(GL_ARRAY_BUFFER, aj_rojo.size()*sizeof(Tupla3f), aj_rojo.data());
      }
   }

   glBindBuffer( GL_ARRAY_BUFFER, id_vbo_ver );       // activar VBO de vértices
   glVertexPointer( 3, GL_FLOAT, 0, 0 );              // especifica formato y offset (=0)
   glBindBuffer( GL_ARRAY_BUFFER, 0 );                // desactivar VBO de vértices.
   glEnableClientState( GL_VERTEX_ARRAY );            // habilitar tabla de vértices

   if(textura != nullptr){
        textura->activar();
        glBindBuffer(GL_ARRAY_BUFFER,id_vbo_ct); //activar VBO de texturas
        glTexCoordPointer(2,GL_FLOAT,0,0);
        glBindBuffer(GL_ARRAY_BUFFER,0); //desactivar VBO de texturas
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
   }

   if(glIsEnabled(GL_LIGHTING)){
      glBindBuffer(GL_ARRAY_BUFFER,id_vbo_nv); //activar VBO de normales
      glNormalPointer(GL_FLOAT,0,0); //especifica formato y offset
      glBindBuffer(GL_ARRAY_BUFFER,0); //desactivar VBO de vértices
      glEnableClientState(GL_NORMAL_ARRAY);
      m.aplicar();
   }

   if(ajedrez)
      glBindBuffer(GL_ARRAY_BUFFER,id_vbo_par); //activa VBO de colores pares
   else{
      switch (color){
      case 0:
         glBindBuffer(GL_ARRAY_BUFFER,id_vbo_col);  
      break;
      case 1:
         glBindBuffer(GL_ARRAY_BUFFER,id_vbo_col);  
      break;
      case 2:
         glBindBuffer(GL_ARRAY_BUFFER,id_vbo_col);  
      break;
      case 3:
         glBindBuffer(GL_ARRAY_BUFFER,id_vbo_coloresSeleccion);  
      break;        
      }
   }

   glColorPointer(3,GL_FLOAT,0,0);
   glBindBuffer(GL_ARRAY_BUFFER,0);
   glEnableClientState(GL_COLOR_ARRAY); //habilita array de colores

   if(ajedrez){
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,id_vbo_par); //activar VBO de caras
      glDrawElements(GL_TRIANGLES,3*pares.size(),GL_UNSIGNED_INT,0); //PINTA LA MITAD DE CARAS DE UN COLOR
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);//desactivar VBO de caras
   }
   else{
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,id_vbo_tri); //activar VBO de caras
      glDrawElements(GL_TRIANGLES,3*f.size(),GL_UNSIGNED_INT,0); //PINTA TODAS LAS CARAS
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);//desactivar VBO de caras        
   }

   glDisableClientState(GL_ARRAY_BUFFER);

   if(ajedrez){ //cambiamos de color
      glBindBuffer(GL_ARRAY_BUFFER,id_vbo_impar); //activa VBO de colores impares
      glColorPointer(3,GL_FLOAT,0,0);
      glBindBuffer(GL_ARRAY_BUFFER,0);
    
      glEnableClientState(GL_COLOR_ARRAY); //habilita array de colores

      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,id_vbo_impar); //activar VBO de caras
      glDrawElements(GL_TRIANGLES,3*impares.size(),GL_UNSIGNED_INT,0); //PINTA LAS CARAS IMPARES DE OTRO COLOR
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);//desactivar VBO de caras
   }

   glDisableClientState(GL_VERTEX_ARRAY); //desactivar uso de array de vértices
   glDisableClientState(GL_ARRAY_BUFFER);  
   
   if(glIsEnabled(GL_LIGHTING))
      glDisableClientState(GL_NORMAL_ARRAY);

   if(glIsEnabled(GL_TEXTURE_2D)){
      glDisableClientState(GL_TEXTURE_COORD_ARRAY);
      glDisable(GL_TEXTURE_2D);
   }
}

// -----------------------------------------------------------------------------
// Función de visualización de la malla,
// puede llamar a  draw_ModoInmediato o bien a draw_ModoDiferido
void Malla3D::draw(unsigned int modo, bool modoLuz, unsigned int color, bool ajedrez)
{
   switch(modo){
      case 0:
         draw_ModoInmediato(ajedrez, color, modoLuz);
         break;

      case 1:
         draw_ModoDiferido(ajedrez, color, modoLuz);
         break;
      }
}

// -----------------------------------------------------------------------------
// Función que calcula las normales para los vértices y las caras
void Malla3D::calcular_normales(){
   Tupla3f normal, a, b;
	float m, m2;
	std::vector<int> aux;

   n_vert.resize(v.size());
	for (int i = 0; i < v.size(); i++){
		n_vert[i] = {0.0,0.0,0.0};
	} 

	for (int i = 0; i < f.size(); i++){
      // Calculamos las componentes necesarias para las normales de caras
      a = v[f[i](1)] - v[f[i](0)];
		b = v[f[i](2)] - v[f[i](0)];
		
      //normal = {a(1) * b(2) - a(2) * b(1), a(2) * b (0) - a(0) * b(2), a(0) * b(1) - a(1) * b(0)};
      //m = sqrt(pow(normal(0), 2) + pow (normal(1), 2) + pow (normal(2), 2));
		
      normal = a.cross(b);

      m = sqrtf(pow(normal(0),2)+pow(normal(1),2) + pow(normal(2),2));
      normal = {normal(0)/m , normal(1)/m , normal(2)/m};

		// Calculamos el vector de normales de vertices
      n_vert[f[i](0)] = n_vert[f[i](0)] + normal;
    	n_vert[f[i](1)] = n_vert[f[i](1)] + normal;
    	n_vert[f[i](2)] = n_vert[f[i](2)] + normal;
	}

   // Normalizamos el vector de normales de vertices
	for(int j = 0; j < n_vert.size(); j++){
      m2 = sqrtf(pow(n_vert[j](0),2)+pow(n_vert[j](1),2) + pow(n_vert[j](2),2));
      n_vert[j] = {n_vert[j](0)/m2 , n_vert[j](1)/m2 , n_vert[j](2)/m2};
   }
}


// -----------------------------------------------------------------------------
void Malla3D::setMaterial(const Material & mat){
   m.setMaterial(mat);
}

void Malla3D::setTextura(Textura * t){
   textura = t;
}

// -----------------------------------------------------------------------------
// P6

void Malla3D::calcularCentroObjeto(){
    for(int i=0; i < v.size(); i++)
        centro_objeto = centro_objeto + v[i];
    
    centro_objeto = centro_objeto/v.size();
}

void Malla3D::transformarCentro(float Tx, float Ty, float Tz, float Sx, float Sy, float Sz){
    centro_transformado(0) = centro_objeto(0)*Sx + Tx;
    centro_transformado(1) = centro_objeto(1)*Sy + Ty;
    centro_transformado(2) = centro_objeto(2)*Sz + Tz;
}

void Malla3D::setColores(Tupla3f color){
   for(int i=0; i < colores[0].size();i++)
      colores[0][i] = color;
}

void Malla3D::setColoresSeleccion(Tupla3f color){
   coloresSeleccion.resize(v.size());
   for(int i=0; i < coloresSeleccion.size(); i++){
      coloresSeleccion[i] = color;
   }
}