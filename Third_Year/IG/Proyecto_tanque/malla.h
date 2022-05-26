// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Malla3D.h
// -- declaraciones de clase Malla3D (mallas indexadas) y derivados
//
// #############################################################################

#ifndef MALLA3D_H_INCLUDED
#define MALLA3D_H_INCLUDED

#include "aux.h"
#include "material.h"
#include "textura.h"

// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************

class Malla3D
{
   public:
      // dibuja el objeto en modo inmediato
      void draw_ModoInmediato(bool ajedrez, unsigned int color, bool modoLuz);

      // dibuja el objeto en modo diferido (usando VBOs)
      void draw_ModoDiferido(bool ajedrez, unsigned int color, bool modoLuz);
      GLuint crearVBO(GLint tipo_vbo, GLint tamanio_bytes, GLvoid * puntero_ram);

      // función que redibuja el objeto está función llama a 'draw_ModoInmediato' (modo inmediato)
      // o bien a 'draw_ModoDiferido' (modo diferido, VBOs)
      void draw(unsigned int modo, bool modoLuz, unsigned int color, bool ajedrez=false);

      // Establecer material
      void setMaterial(const Material & mat);

      // Establecer textura
      void setTextura(Textura * t);

      // Establecer color
      void setColores(Tupla3f color);

      // Establecer el color del objeto seleccionado
      void setColoresSeleccion(Tupla3f color);

      // Obtener el color del objeto seleccionado
      Tupla3f getColorSeleccion(){
         return {((float) coloresSeleccion[0](0)),((float)coloresSeleccion[0](1)),((float)coloresSeleccion[0](2))};
      }

      // Obtener el centro del objeto seleccionado
      Tupla3f getCentroSeleccion(){
         return centro_transformado;
      }

      // Obtener centro del objeto
      Tupla3f getCentro(){
         return centro_objeto;
      }
      
      void transformarCentro(float Tx=0, float Ty=0, float Tz=0, float Sx=1, float Sy=1, float Sz=1);

   protected:

      int id_vbo_ver = 0, id_vbo_tri = 0, id_vbo_col = 0;
      int id_vbo_par = 0, id_vbo_impar = 0, id_vbo_rojo = 0, id_vbo_verde = 0;
      int id_vbo_nv=0, id_vbo_ct=0, id_vbo_coloresSeleccion=0; 
      
      void calcular_normales() ;                         // Calcula tabla de normales de vértices (práctica 3)
      void calcularCentroObjeto();                       // Calcula el centro del objeto

      std::vector<Tupla3f> v ;                           // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
      std::vector<Tupla3i> f ;                           // una terna de 3 enteros por cada cara o triángulo
      std::vector<std::vector<Tupla3f>> colores;         // Una terna de ternas de 3 float para almacenar los colores en los distindos modos
      
      //Tablas de cara y colores para el modo de visualizacion de ajedrez
      std::vector<Tupla3i> pares, impares;               // tabla de caras para el modo ajedrez
      std::vector<Tupla3f> aj_verde, aj_rojo;            // tabla de colores para el modo ajedrez

      // tabla de normales de vértices y caras
      std::vector<Tupla3f> n_vert;
      std::vector<Tupla3f> n_caras;
   
      // Tipo material
      Material m;

      // Texturas
      Textura * textura = nullptr;
      std::vector <Tupla2f > ct;

      // Elementos para la p6
      std::vector<Tupla3f> coloresSeleccion;
      Tupla3f centro_objeto = {0,0,0};
      Tupla3f centro_transformado = {0,0,0};
};


#endif
