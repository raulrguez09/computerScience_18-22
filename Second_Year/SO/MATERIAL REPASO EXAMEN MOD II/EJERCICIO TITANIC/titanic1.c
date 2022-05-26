#include <dirent.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<unistd.h>
#include <ftw.h>

#define archivo "titanic.csv"

int main(void){
    int fd[2];
    
    if(pipe(fd)<0){
        perror("ERROR EN PIPE");
        exit(EXIT_FAILURE);
    }

    if(fork()==0){
        close(fd[0]);
        dup2(fd[1],STDOUT_FILENO);
        execlp("cut","cut","-d",";","-f","6",archivo,NULL);
    }

    close(fd[1]);

    unsigned int  n=0,max_edad=0, menores_5=0,suma=0;
    int min_edad=-1;
    double media;

    unsigned int leido;
    char raw[3]={0};
    while(read(fd[0],raw,2)){
        leido=atoi(raw);
        n++;
        suma+=leido;
        if(min_edad==-1 || leido<min_edad)
            min_edad=leido;
        if(leido>max_edad)
            max_edad=leido;
        if(leido<5)
            menores_5++;
        read(fd[0],raw,1); //PARA \n
    }
    media=suma/n;
    
    
    printf("Total personas: %u\n",n);
    printf("Media edad: %f\n",media);
    printf("Más joven: %i\n",min_edad);
    printf("Más viejo: %u\n",max_edad);
    printf("Menores de 5 años: %u\n",menores_5);






    exit(EXIT_SUCCESS);



}