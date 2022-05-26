#include <dirent.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<unistd.h>
#include <ftw.h>

#define PERMISOS 0702

int main(int argc, char *argv[]){

    DIR *midir;
    struct dirent *entrada;
    char ruta[256];

    if((midir = opendir("./quijote"))==NULL){
        perror("OPENDIR");
        exit(EXIT_FAILURE);
    }

    while((entrada=readdir(midir))!=NULL){
        struct stat a;
        strcpy(ruta,"quijote/");
        strcat(ruta,entrada->d_name);
        if(stat(ruta,&a)<0){
            perror("\nERROR EN STAT\n");
        }
        if(strcmp(entrada->d_name,".")==0) continue;
        if(strcmp(entrada->d_name,"..")==0) continue;
        if(S_ISREG(a.st_mode) && ((a.st_mode & 0702)==0702)){
            FILE *fich;
            fich=fopen(ruta,"r");
            fseek(fich,0l,SEEK_END);
            int espacio=ftell(fich);
            fclose(fich);
            printf("%d",espacio);
        }
    }

    return 0;
}
