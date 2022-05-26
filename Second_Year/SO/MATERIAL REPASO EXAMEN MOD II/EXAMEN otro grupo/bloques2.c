//CRISTIAN FERNÁNDEZ JIMÉNEZ DNI:20623057S
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


int main(int argc, char* argv[]){
    int fd[2];
	int pids[argc-1];

    if(argc<2){
	perror("Error de ejecución: SE HAN DE INTRODUCIR 2 ARGUMENTOS O MÁS:\n bloques2 rutaarchivo1 ruta archivo2 ...");
	exit(EXIT_FAILURE); 

    }

    if(pipe(fd)<0){
        perror("ERROR EN PIPE");
        exit(EXIT_FAILURE);
    }

	for(int i=1; i<argc; i++)
    if((pids[i-1]=fork())==0){
        close(fd[0]);
        dup2(fd[1],STDOUT_FILENO);
        execlp("du","du","-k",argv[i],NULL);
    }

    //else{

		char informacion[256]="";
		char nombre[256]="/tmp/dato_";
        close(fd[1]);
        dup2(fd[0],STDIN_FILENO);
		char buf[2];
		int contador=1;
		umask(0);
		char valor[10];
		while(read(STDIN_FILENO,buf,1)){
			sprintf(informacion,"%s%c",informacion,buf[0]);

			if(buf[0]=='\n'){
				snprintf(nombre,256,"%s%d","/tmp/dato_",contador); //NECESITA EL NUMERO MAGICO
				int tmp;

				if((tmp=open(nombre,O_CREAT|O_TRUNC|O_WRONLY,0777))<0){
					perror("Error en open de archivo");
					printf("%s\n",nombre);
					exit(EXIT_FAILURE);
				}

				write(tmp,informacion,strlen(informacion));
				close(tmp);
				write(STDOUT_FILENO,informacion,strlen(informacion));

				sprintf(informacion,"%s","");
				contador++;
			}

		}


		for(int i=0; i<argc-1; i++)
			wait(&pids[i]);   
	//}
    

    exit(EXIT_SUCCESS);



}
