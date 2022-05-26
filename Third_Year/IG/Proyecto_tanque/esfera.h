// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: esfera.h

//
// #############################################################################
#ifndef ESFERA_H_INCLUDED
#define ESFERA_H_INCLUDED

#include "aux.h"
#include "objrevolucion.h"

class  Esfera : public  ObjRevolucion{
    public:
        Esfera( const  int  num_vert_perfil ,const  int  num_instancias_perf, bool textura_act, const  float  radio, char eje);

} ;


#endif