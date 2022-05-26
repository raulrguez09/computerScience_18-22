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

#define MAX_CHAR 256


int main(int args, char* argv[]){
    int fd[2];
	 pid_t pid;

	if(args<2){
		perror("Parametros incorrectos\nIntroducir netflix <serie_netflix>");
		exit(EXIT_FAILURE);
	}

    if(pipe(fd)<0){
        perror("Error en pipe ");
        exit(EXIT_FAILURE);
    }

    if((pid=fork())==0){
        close(fd[0]);
        dup2(fd[1],STDOUT_FILENO);
        execlp("ls","ls","-i",NULL);
    }

    else{
        close(fd[1]);
        dup2(fd[0],STDIN_FILENO);
		  char buf[2];
		  int contador=0;
        int suma=0;
		  char nombre[MAX_CHAR]="/tmp/";
		  char inodo[MAX_CHAR]="";
		  unsigned encontrado=0;
		  char numero[2];
		  umask(0);
		  while(read(STDIN_FILENO,buf,1)){

				if(encontrado){
				sprintf(nombre,"%s%c",nombre,buf[0]);
				}

				if(buf[0]=='\n'){
					encontrado=0;
					contador++;

					for(int i=0; i<strlen(nombre); i++)
						if(nombre[i]=='\n')
								nombre[i]='\0';
					if(!strcmp(nombre,"/tmp/netflix.txt")){
						int net;
						if((net=open("/tmp/series_recomendadas.txt",O_CREAT|O_WRONLY,S_IRWXU|S_IRGRP|S_IXGRP|S_IXOTH))<0){
							perror("Error en open de archivo");
							exit(EXIT_FAILURE);
						}
						lseek(net,0,SEEK_END);
						write(net,argv[1],strlen(argv[1]));
						write(net,"\n",strlen("\n"));
						close(net);
						}
					int tmp;
					if((tmp=open(nombre,O_CREAT|O_TRUNC|O_WRONLY,S_IRWXU|S_IRWXG))<0){
						perror("Error en open de archivo");
						exit(EXIT_FAILURE);
					}

					write(tmp,inodo,strlen(inodo));
					close(tmp);
					snprintf(nombre,MAX_CHAR,"%s","/tmp/");
					sprintf(inodo,"%s","");
				}

				if(buf[0]==' '){
					encontrado=1;
					suma=suma+atoi(numero);
				}				

				if(encontrado==0){
					sprintf(inodo,"%s%c",inodo,buf[0]);
					numero[0]=buf[0];
					numero[1]='\0';
				}

			}
    		
			char contenido[MAX_CHAR]="";

			sprintf(contenido,"Suma inodos: %d\nTotal entradas: %d",suma,contador);
    		int res;
			if((res=open("resultado.txt",O_CREAT|O_TRUNC|O_WRONLY,0666))<0){
				perror("Error en open de archivo");
				exit(EXIT_FAILURE);
			}

			write(res,contenido,strlen(contenido));
			close(res);

			int estado=pid;
			wait(&estado);
			
		}

		return 0;
}
