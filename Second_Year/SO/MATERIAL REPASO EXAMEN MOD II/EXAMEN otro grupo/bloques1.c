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
	perror("Error de ejecución: SE HAN DE INTRODUCIR 2 ARGUMENTOS O MÁS:\n bloques1 rutaarchivo1 ruta archivo2 ...");
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
        close(fd[1]);
        dup2(fd[0],STDIN_FILENO);
		char buf[2];
		while(read(STDIN_FILENO,buf,1)){
			write(STDOUT_FILENO,buf,1);	
		}


		for(int i=0; i<argc-1; i++)
			wait(&pids[i]);   
	//}
    

    exit(EXIT_SUCCESS);


//COGER N lineas y si supera, ir eliminando al principio


}
