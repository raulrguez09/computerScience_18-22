// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Cubo.h

//
// #############################################################################

#ifndef OBJREVOLUCION_H_INCLUDED
#define OBJREVOLUCION_H_INCLUDED

#include "aux.h"
#include "malla.h"
#include <bits/stdc++.h>

// *****************************************************************************
//
// clases derivadas de Malla3D (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************
// Cubo con centro en el origen y lado unidad por defecto
// (tiene 9 vertices y 6 caras)

class ObjRevolucion : public Malla3D
{
public:
    int instancias;
    bool tapaSup, tapaInf;
    bool texturaActiva = false;
    ObjRevolucion();
    ObjRevolucion(const std::string & archivo, int num_instancias, bool textura_act, bool tapa_sup=true, bool tapa_inf=true) ;
    ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, bool tapa_sup=true, bool tapa_inf=true) ;
    Tupla3f rotacionEje(std::vector<Tupla3f> perfil_original, char eje, int j, float coseno, float seno);
    
    //dibujar
    void draw(unsigned int modo, bool modoLuz, unsigned int color, bool ajedrez, bool tapaSup, bool tapaInf);
    void draw_ModoInmediato(bool ajedrez, unsigned int color, bool modoLuz, bool tapaSup, bool tapaInf);
    void draw_ModoDiferido(bool ajedrez, unsigned int color, bool modoLuz, bool tapaSup, bool tapaInf);
    GLuint crearVBOrev(GLint tipo_vbo, GLint tamanio_bytes, GLvoid * puntero_ram);

    //texturas
    void crearTextura(std::vector<Tupla3f> perfil_original, int num_instancias);
protected:
    void crearMalla( const std::vector<Tupla3f> perfil_original, const int num_instancias, bool textura_act, char eje, int color, bool tapa_sup=true, bool tapa_inf=true);
} ;




#endif
