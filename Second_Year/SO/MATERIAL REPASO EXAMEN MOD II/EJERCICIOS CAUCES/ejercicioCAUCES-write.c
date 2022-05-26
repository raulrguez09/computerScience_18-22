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
    int fd[2],fd2[2];

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
        if(pipe(fd2)<0){
            perror("ERROR EN PIPE 2");
            exit(EXIT_FAILURE);
        }

        dup2(fd[0],STDIN_FILENO);

        if(fork()==0){
            close(fd2[0]);
            dup2(fd2[1],STDOUT_FILENO);
            if(args>1)
                execlp("tail","tail",argumentoS,NULL);
            else
                execlp("tail","tail",NULL);
        }
        else{
            close(fd2[1]);
            dup2(fd2[0],STDIN_FILENO);
            char buf[2];
            _Bool espacio=0;
            while(read(0,buf,1)){
                if(!espacio)
                    write(1,buf,1);
                if(buf[0]==' ')
                    espacio=1;

                if(espacio){
                    if(buf[0]=='\n'){
                    write(1,"\n",1);
                    espacio=0;
                    }
                }
            }
            //execlp("cut","cut","-d"," ","-f","1",NULL);
        }
	}    

    exit(EXIT_SUCCESS);

}
