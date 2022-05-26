
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>  	/* Primitive system data types for abstraction\
			   of implementation-dependent data types.
			   POSIX Standard: 2.6 Primitive System Data Types
			   <sys/types.h>
			*/
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
#include <string.h>

char buf1[80];
char buf2[]="~BLOQUE ";

int main(int argc, char *argv[])
{
int fd, fd2;
int numRead=1;
if (argc == 0){
	printf("\nIntroducir texto: ");
	

}

else if( (fd=open(argv[1],O_RDWR,S_IRUSR|S_IWUSR))<0) {
	printf("\nError %d en open entrada",errno);
	perror("\nError en open");
	exit(EXIT_FAILURE);
}

if( (fd2=open("salida.txt",O_CREAT|O_WRONLY,S_IRUSR|S_IWUSR))<0) {
	printf("\nError %d en open salida",errno);
	perror("\nError en open");
	exit(EXIT_FAILURE);
}

int contador=1;
while (numRead != 0 ){
char contadorS[10];
sprintf(contadorS, "%d", contador);
strcat(contadorS, "~");

	if((numRead=read(fd,buf1,80)) < 0) {
		perror("\nError en read");
		exit(EXIT_FAILURE);
	}
	if(write(fd2, buf1,numRead)<0){
	perror("\nError en write archivo salida.txt");
	exit(EXIT_FAILURE);
	}
	if(lseek(fd,0,SEEK_CUR) < 0){
	perror("\nError en lseek archivo entrada");
	exit(EXIT_FAILURE);
	}
	if(lseek(fd2,0,SEEK_CUR) < 0){
	perror("\nError en lseek archivo salida.txt");
	exit(EXIT_FAILURE);
	}

	if(write(fd2, buf2,8)<0){
	perror("\nError en write archivo salida.txt");
	exit(EXIT_FAILURE);
	}
	lseek(fd2,0,SEEK_CUR);
	write(fd2, contadorS, 2);

	if(lseek(fd2,0,SEEK_CUR) < 0){
	perror("\nError en lseek archivo salida.txt");
	exit(EXIT_FAILURE);
	}

contador=contador+1;	
	
}


return EXIT_SUCCESS;
}
