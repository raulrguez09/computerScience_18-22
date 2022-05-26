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

/*char **obtener_datos(int total_datos, char*buf){
	char *datos[total_datos];
	char *t;
	int i=0;
	t = strtok(buf, "|");
	while( t != NULL){
		datos[i] = t;
		t = strtok(NULL, "|");
		i++;	
	}

	return datos;

}*/

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
	execlp("./EJERCICIOnftw","EJERCICIOnftw",NULL);
}

else{
	close(fd[1]);
	dup2(fd[0],STDIN_FILENO);
	char buf[2];
	char cadena[80]="";
	while(read(0,buf,1)){
		if(strcmp(buf,"\n")){
			sprintf(cadena, "%s%s",cadena,buf);
		}
		else{
			char *datos[3];
			char *t;
			int i=0;
			t = strtok(cadena, "|");
			while( t != NULL){
				datos[i] = t;
				t = strtok(NULL, "|");
				i++;	
			}			
			char* nombre=datos[0];
			char* permisos=datos[1];
			char* tamanio=datos[2];
			t=strtok(nombre,"/");
			while( t != NULL){
				nombre = t;
				t = strtok(NULL, "/");	
			}	
			char direccion[12]="";
			sprintf(direccion,"%s%s","./tmp/",nombre);
			int tmp;
			umask(0);
			if((tmp=open(direccion,O_CREAT|O_TRUNC|O_WRONLY,strtol(permisos,NULL,8)))<0){
				perror("ERROR EN OPEN\n");
				printf("archivo: %s\n",direccion);
				exit(EXIT_FAILURE);
			}

			//0702 PONE BIEN LOS PERMISOS, SI METEMOS 702 FALLA -> solucion: strol(cadena,NULL,8)

			write(tmp,tamanio,strlen(tamanio));
			
		}
	}


}
return EXIT_SUCCESS;


}
