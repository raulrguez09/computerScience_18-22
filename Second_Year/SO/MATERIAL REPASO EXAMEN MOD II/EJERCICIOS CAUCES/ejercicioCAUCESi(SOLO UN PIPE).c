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
#include <ftw.h>

/*EJERCICIO TIPO EXAMEN: 
Crear un programa en C de tal forma que realice el siguiente cauce en linux:
ls -l | tail -N
donde N será un entero pasado como parámetro al programa
Y además, crear otro hijo que muestre solo los permisos de esas N líneas
*/

int main(int args, char* argv[]){
    int fd[2];

    int argumento;
    char argumentoS[3];
    if(args>1){
       argumento=atoi(argv[1]);
        sprintf(argumentoS,"-%d",argumento);

    }

    if(pipe(fd)<0){
        perror("ERROR EN PIPE");
        exit(EXIT_FAILURE);
    }

    if(fork()==0){
        close(fd[0]);
        dup2(fd[1],STDOUT_FILENO);
        execlp("ls","ls","-l",NULL);
    }

    else{
        close(fd[1]);
        dup2(fd[0],STDIN_FILENO);
        if(args>1)
        execlp("tail","tail",argumentoS,NULL);
        else
            execlp("tail","tail",NULL);
    
    
	}
    

    exit(EXIT_SUCCESS);


//COGER N lineas y si supera, ir eliminando al principio


}
