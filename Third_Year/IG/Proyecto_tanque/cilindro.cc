#include "aux.h"
#include "cilindro.h"
#include "math.h"

Cilindro::Cilindro( const  int  num_vert_perfil , int  num_instancias_perf ,const  float  altura ,const  float  radio, char eje, int ext){
    std::vector<Tupla3f> perfil;
	float x, y, z;
		
	for (int i = 0; i <= num_vert_perfil; i++){
		x = radio;
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
	}

	if(ext == 0){	
		crearMalla (perfil, num_instancias_perf, false, eje, 1, true, true);
	}else if(ext == 1){
		crearMalla (perfil, num_instancias_perf,false, eje, 0, false, false);
	}else{
		crearMalla (perfil, num_instancias_perf,false, eje, 0, true, false);
	}
}