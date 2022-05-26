// *****************************************************************************
//
// Clase Luz 
//
// *****************************************************************************

#ifndef _LUZ_H
#define _LUZ_H

#include "aux.h"

class Luz 
{
	public:
	    void activar();
		void desactivar();
	    bool esta_activa();

	protected:
		GLenum id;
		Tupla4f posicion;
		Tupla4f colorAmbiente;
		Tupla4f colorDifuso;
		Tupla4f colorEspecular;
		bool activa;
};

#endif