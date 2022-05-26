//CRISTIAN FERNÁNDEZ JIMÉNEZ DNI:20623057S
#include <dirent.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<unistd.h>
#include <ftw.h>

/*EJERCICIO TIPO EXAMEN: 
Crear un programa en C de tal forma que realice el siguiente cauce en linux:
ls -l | wc -l
Y además, como ese cauce escribirá en consola el número de líneas, decir si ese 
número es par o impar
*/

int main(void){
    int fd[2],fd2[2];
    int lineas;
    
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
            perror("ERROR EN PIPE");
            exit(EXIT_FAILURE);
        }

        if(fork()==0){
            dup2(fd[0],STDIN_FILENO);
            close(fd2[0]);
            dup2(fd2[1],STDOUT_FILENO);
            execlp("wc","wc","-l",NULL);  
        }

        else{
            char raw;
            char numero[3];
            close(fd2[1]);

            if(read(fd2[0],&raw,1024) <= 0){
                perror("ERROR DE LECTURA");
                exit(EXIT_FAILURE);
            }

            lineas=strtol(&raw,0,10);

            printf("%d (%s\n",lineas,lineas%2?"IMPAR)":"PAR)");
        }
      
    }
    exit(EXIT_SUCCESS);



}
