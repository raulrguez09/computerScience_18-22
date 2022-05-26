#include <dirent.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<unistd.h>
#include <ftw.h>

int main(void){

    int fd[2], fd3[2];

    if(pipe(fd)<0){
        perror("ERROR EN PIPE");
        exit(EXIT_FAILURE);
    }

    if(fork()==0){
        close(fd[0]);
        dup2(fd[1],STDOUT_FILENO);
        execlp("./tam_quijote","tam_quijote",NULL);
    }
    
    else{
        close(fd[1]);

        if(pipe(fd3)<0){
            perror("ERROR EN PIPE");
            exit(EXIT_FAILURE);
        }

        dup2(fd[0],STDIN_FILENO);

        if(fork()==0){
            close(fd3[0]);
            dup2(fd3[1],STDOUT_FILENO);
            execlp("wc","wc","-w","quijote/quijote.txt",NULL);
        }
        
        else{
            int fd2;
            close(fd3[1]);
            dup2(fd3[0],STDIN_FILENO);
            if((fd2=open("resultado.txt",O_CREAT|O_RDWR|O_TRUNC,S_IRUSR|S_IWUSR))<0){
                perror("\nError en open");
                exit(EXIT_FAILURE);
            }

            int tamano;
            char raw[2];
            char *cadena="Tamaño quijote.txt: ";
            write(fd2,cadena,strlen(cadena));
            while(read(fd[0],raw,1))
                write(fd2,raw,1);
            write(fd2,"\n\n",sizeof("\n\n"));
                    
            cadena="Palabras: ";
            write(fd2,cadena,strlen(cadena));
            while(read(fd3[0],raw,1)){
                if(raw[0]==' ')
                    break;
                write(fd2,raw,1);
            }
            }
    }

    return 0;

}
