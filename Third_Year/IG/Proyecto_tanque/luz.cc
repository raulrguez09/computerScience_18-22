#include "luz.h"

bool Luz::esta_activa(){

	return activa;

}

void Luz::activar(){
        glLightfv(id, GL_AMBIENT, colorAmbiente);
        glLightfv(id, GL_DIFFUSE, colorDifuso);
        glLightfv(id, GL_SPECULAR, colorEspecular);
        glLightfv(id, GL_POSITION, posicion);
        glEnable(id);
}

void Luz::desactivar(){
        glDisable(id);
}