// programa que cambia los permisos de los archivos de un directorio dado un octal como argumento

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
  char mensajeerror[]="\nDebe dar 2 arguments: ruta de un directorio y número octal de 4 cifras\n";
  DIR *midir;
  struct dirent *entrada;  // mi_dirent es un puntero a una estructura
  int permisos;
  char ruta[256];
  if( argc != 3 )
  { 
    	write(STDERR_FILENO, mensajeerror, strlen(mensajeerror));
    	exit(EXIT_FAILURE);
  }

  
  permisos=strtol(argv[2],NULL,8);
  if( (midir = opendir( argv[1])) == NULL )
  {   perror( "opendir" );
	exit(EXIT_FAILURE);
   }
   while( (entrada = readdir( midir )) != NULL ){
	struct stat a;
	strcpy(ruta,argv[1]);
        strcat(ruta, "/");
	strcat(ruta, entrada->d_name);
	if(stat(ruta,&a)<0){
	perror("\nError en stat\n");
	}
	int permisosantiguos=(a.st_mode & 0777);
	if (strcmp(entrada->d_name,".")==0)      continue;
	if (strcmp(entrada->d_name,"..")==0)     continue;

	if(chmod(ruta, permisos) < 0) {
		perror("\nError en chmod");
		printf( "%s : %s %o\n", entrada->d_name,strerror(errno),permisosantiguos);
	}
	else{
	printf( "%s : %o %o\n", entrada->d_name,permisosantiguos,permisos);
	}
   }  
  closedir( midir );	
  exit(EXIT_SUCCESS);
}

