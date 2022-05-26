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
    int fd;
	int pids[argc-1];

    if(argc<2){
	perror("Error de ejecución: SE HAN DE INTRODUCIR 2 ARGUMENTOS O MÁS:\n bloques1 rutaarchivo1 ruta archivo2 ...");
	exit(EXIT_FAILURE); 

    }
	umask(0);
	mkfifo("ArchivoFIFO",0666);

	if( (fd=open("ArchivoFIFO",O_RDWR)) <0){
		perror("Error en apertura de FIFO");
		exit(EXIT_FAILURE);
	}

	for(int i=1; i<argc; i++)
    if((pids[i-1]=fork())==0){
        dup2(fd,STDOUT_FILENO);
        execlp("du","du","-k",argv[i],NULL);
    }

    //else{

		char buf[2];
		int contador=1;
		while(read(fd,buf,1)){
			if(buf[0]=='\n')
				contador++;

			write(STDOUT_FILENO,buf,1);	
			if(contador==argc)
				break;

			
		}

		close(fd);


		for(int i=0; i<argc-1; i++)
			wait(&pids[i]);   
	//}
    

    exit(EXIT_SUCCESS);


//COGER N lineas y si supera, ir eliminando al principio


}
