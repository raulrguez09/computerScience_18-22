#define _XOPEN_SOURCE 500

#include <dirent.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<unistd.h>
#include <ftw.h>
#define S_PERMISOS(mode) ((mode & 0777)==0702)

/*EJERCICIO TIPO EXAMEN: 
Realizar exploración completa de todas las entradas del directorio <<ficheros>> utilizando nftw
Filtrar po:
-	ARCHIVOS REGULARES
-	TODOS PERMISOS PARA USER, NINGUNO PARA GROUP, ESCRITURA PARA OTHER
-	LONGITUD DEL NOMBRE DEL ARCHIVO > 7
Por cada entrada escribir una cadena de caracteres por la salida estandar que siga 
este formato: nombre|permisos|tamaño
*/

int visitar(const char* path, const struct stat* stat, int flags, struct FTW *ftw){

	char cadena[100];

	if(strlen(path)>7 && S_ISREG(stat->st_mode) && S_PERMISOS(stat->st_mode) ){

//SI PONEMOS & 0702 MUESTRA LOS DE 0777 Y 0702, SI PONEMOS & 0777, SOLO MOSTRARÁ LOS ULTIMOS

	sprintf(cadena, "%s|%o|%d\n", path, stat->st_mode & ~S_IFMT,(int) stat->st_size);

	write(STDOUT_FILENO, cadena, strlen(cadena));

	}

	return 0;
}

int main( int argc, char *argv[] )
{

		//dirpath, func,   MAS_FDS FLAGS
if(nftw("./ficheros", visitar, 10, 0) != 0){
perror("ERROR EN LA BÚSQUEDA RECURSIVA");
exit(EXIT_FAILURE);
}

return EXIT_SUCCESS;


}
