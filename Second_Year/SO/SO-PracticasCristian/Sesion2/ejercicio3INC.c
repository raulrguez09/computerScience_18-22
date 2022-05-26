// programa que localiza todos los archivos regulares dentro de un directorio dado, con permiso de ejecucion para el grupo y para otros.
//Debe devolver el nombre, inodo y la suma total de espacio en bytes


#include <dirent.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<unistd.h>

int main( int argc, char *argv[] )
{
  char mensajeerror[]="\nDebe dar 1 argumento: ruta de un directorio(por defecto se toma el directorio actual)\n";
  DIR *midir;
  struct dirent *entrada;  // mi_dirent es un puntero a una estructura
  char rutain[256];
  char ruta[256];
  int contador=0;
  int espacio=0;
  if( argc != 2 )
  { 
    	strcpy(rutain,".");
  }
  else
	strcpy(rutain,argv[1]);

  if( (midir = opendir(rutain)) == NULL )
  {   perror( "opendir" );
	exit(EXIT_FAILURE);
   }
	
printf("Los i-nodos son:\n");
   while( (entrada = readdir( midir )) != NULL ){
	struct stat a;
	strcpy(ruta,rutain);
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

printf("Existen %d archivos regulares con permiso x para grupo y otros\n",contador);
printf("El tamaño total ocupado por dichos archivos es %d bytes\n", espacio);
  closedir( midir );	
  exit(EXIT_SUCCESS);
}

