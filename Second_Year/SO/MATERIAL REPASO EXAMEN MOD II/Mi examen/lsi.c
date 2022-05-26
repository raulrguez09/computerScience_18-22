#define _XOPEN_SOURCE 500
//CRISTIAN FERNÁNDEZ JIMÉNEZ 20623057S

#include <dirent.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ftw.h>

//#define REGLA(path,stat)((S_ISREG(stat->st_mode) || S_ISDIR(stat->st_mode)) && ((stat->st_mode & 0777)==0777) && strlen(path)>7 && stat->st_size>1 )
#define REGLA(mode,tamano,longitud)((S_ISREG(mode) || S_ISDIR(mode)) && ((mode & 0777)==0777) && longitud>7 && tamano>1 )
int main(int argc, char *argv[]){

    DIR *midir;
    struct dirent *entrada;
    char ruta[256];

    if((midir = opendir("."))==NULL){
        perror("Error en opendir");
        exit(EXIT_FAILURE);
    }

    while((entrada=readdir(midir))!=NULL){
        struct stat a;
        strcpy(ruta,"");
        strcat(ruta,entrada->d_name);
        if(stat(ruta,&a)<0){
            perror("\nERROR EN STAT\n");
        }
        if(strcmp(entrada->d_name,".")==0) continue;
        if(strcmp(entrada->d_name,"..")==0) continue;
        if(REGLA(a.st_mode,a.st_size,strlen(ruta)))
				printf("%ld %s\n",a.st_ino,ruta);
        
			/*if((S_ISREG(a.st_mode) || S_ISDIR(a.st_mode)) && ((a.st_mode & 0777)==0777) && strlen(ruta)>7 && (a.st_size)>1)
							printf("%ld %s\n",a.st_ino,ruta);*/
    }

    return 0;
}
