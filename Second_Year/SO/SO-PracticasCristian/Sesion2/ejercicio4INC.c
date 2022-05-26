// programa que localiza todos los archivos regulares dentro de un directorio dado, con permiso de ejecucion para el grupo y para otros.
//Debe devolver el nombre, inodo y la suma total de espacio en bytes

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
  int espacio=0;
int contador=0;
static int buscar(const char *fpath, const struct stat *sb, int tflag, struct FTW *ftwbuf){
  char ruta[256];
  strcpy(ruta, fpath);
  DIR *midir;
  struct dirent *entrada;

  22if( (midir = opendir(ruta)) == NULL )
  {   perror( "opendir" );
	exit(EXIT_FAILURE);
   }
	
printf("Los i-nodos son:\n");
   while( (entrada = readdir( midir )) != NULL ){
	struct stat a;
	strcpy(ruta,fpath);
	strcat(ruta,"/");
	strcat(ruta, entrada->d_name);
	if(stat(ruta,&a)<0){
	perror("\nError en stat");
	printf("--> %s\n",ruta);
	}
	if (strcmp(entrada->d_name,".")==0)      continue;
	if (strcmp(entrada->d_name,"..")==0)     continue;

	if((a.st_mode & 0170011)==0100011) {
		printf( "%s : %ld\n", ruta,a.st_ino);
		contador++;
		FILE *fich;
  		fich=fopen(ruta,"r");
  		fseek(fich, 0L, SEEK_END);
		espacio+=ftell(fich);
		fclose(fich);
	}
   }  



closedir(midir);
return 0;
}
int main( int argc, char *argv[] )
{

if (nftw((argc <2) ? "." : argv[1], buscar, 20, FTW_D | FTW_DEPTH) == -1){
perror("nftw");
exit(EXIT_FAILURE);
}

printf("Existen %d archivos regulares con permiso x para grupo y otros\n",contador);
printf("El tamaño total ocupado por dichos archivos es %d bytes\n", espacio);
  exit(EXIT_SUCCESS);
}

