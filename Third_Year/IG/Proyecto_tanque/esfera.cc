#include "aux.h"
#include "malla.h"
#include "esfera.h"
#include "math.h"

Esfera::Esfera( const  int  num_vert_perfil ,const  int  num_instancias_perf, bool textura_act, const  float  radio, char eje){
    const float PI = 3.14159265;
    //Tupla3f origen = {0.0, 0.0, 0.0};
    std::vector<Tupla3f> perfil;
	float x, y, z;

	//perfil.push_back({origen(0)*5, (origen(1) - radio)*5, origen(2)*5});
		
	for (int i = 1; i <= num_vert_perfil - 1; i++){
		x = radio*cos(((PI*i)/num_vert_perfil) + 3*PI/2);
		y = radio*sin(((PI*i)/num_vert_perfil) + 3*PI/2);
		z = 0.0;
		switch(eje){
			case 'x':
				perfil.push_back({y, x, z});
			break;
			case 'y':
				perfil.push_back({x, y, z});
			break;
			case 'z':
				perfil.push_back({z, y, x});
			break;
		}
	}

	//perfil.push_back({origen(0)*5, (origen(1) + radio)*5, origen(2)*5});

    crearMalla(perfil, num_instancias_perf, textura_act, eje, 0, true, true);
}