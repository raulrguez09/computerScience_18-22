#include "aux.h"
#include "malla.h"
#include "cono.h"

Cono::Cono( const  int  num_vert_perfil ,const  int  num_instancias_perf, const  float  altura ,const  float  radio, char eje){
	std::vector<Tupla3f> perfil;
    float x, y, z;

	for (int i = 0; i <= num_vert_perfil; i++){
		x = radio - i*radio/num_vert_perfil;
		y = i*altura/num_vert_perfil;
		z = 0.0;
		switch(eje){
			case 'x':
				perfil.push_back({y*3, x*3, z*3});
			break;
			case 'y':	
				perfil.push_back({x*3, y*3, z*3});
			break;
			case 'z':
				perfil.push_back({x*3, z*3, y*3});
			break;
		}
		//std::cout << perfil[i] << std::endl;
	} 

    crearMalla (perfil, num_instancias_perf, eje, 0, true, true);
}