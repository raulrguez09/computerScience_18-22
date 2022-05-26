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


/*EJERCICIO TIPO EXAMEN: 
Realizar exploración completa de todas las entradas del directorio <<ficheros>> utilizando nftw
Filtrar po:
-	ARCHIVOS REGULARES
-	TODOS PERMISOS PARA USER, NINGUNO PARA GROUP, ESCRITURA PARA OTHER
-	LONGITUD DEL NOMBRE DEL ARCHIVO > 7
Por cada entrada escribir una cadena de caracteres por un archivo de salida que siga 
este formato: nombre|permisos|tamaño
*/

int visitar(const char* path, const struct stat* stat, int flags, struct FTW *ftw){

	char cadena[100];

	if(strlen(path)>7 && S_ISREG(stat->st_mode) && ((stat->st_mode & 0702)==0702)){

	sprintf(cadena, "%s|%o|%d\n", path, stat->st_mode & ~S_IFMT,(int) stat->st_size);

	write(STDOUT_FILENO, cadena, strlen(cadena));

	}

	return 0;
}

int main( int argc, char *argv[] )
{
int fd[2], archivo;
if(pipe(fd)<0){
	perror("Error en PIPE");
	exit(EXIT_FAILURE);
}

if(fork()==0){
	close(fd[0]);
	dup2(fd[1],STDOUT_FILENO);
	if(nftw("./ficheros", visitar, 10, 0) != 0){
	perror("ERROR EN LA BÚSQUEDA RECURSIVA");
	exit(EXIT_FAILURE);
	}
}

else{
	close(fd[1]);
	dup2(fd[0],STDIN_FILENO);
	archivo=open("salidaEJ.txt",O_CREAT|O_TRUNC|O_WRONLY,S_IRUSR|S_IWUSR);
	char buf[2];
	while(read(0,buf,1)){
		write(archivo,buf,1);
	}

}
return EXIT_SUCCESS;


}
