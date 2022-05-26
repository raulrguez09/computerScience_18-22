#include<sys/types.h>	//Primitive system data types for abstraction of implementation-dependent data types.
						//POSIX Standard: 2.6 Primitive System Data Types <sys/types.h>
#include<unistd.h>		//POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include<stdio.h>
#include<errno.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
if(argc<2){
perror( "INTRODUCIR UN ARGUMENTO ENTERO" );
exit(EXIT_FAILURE);
}

char bufpar[]="Es par\n";
char bufimpar[]="Es impar\n";
char bufd[]="Es divisible por 4\n";
char bufi[]="NO es divisible por 4\n";
int entero=strtol(argv[1],NULL,10);
pid_t pid;
if( (pid=fork())<0) {
	perror("\nError en el fork");
	exit(EXIT_FAILURE);
}
else if(pid==0) {  
	//proceso hijo ejecutando el programa
	if(entero%2==0){
	if(write(STDOUT_FILENO,bufpar,sizeof(bufpar)) != sizeof(bufpar)) {
		perror("\nError en write");
		exit(-1);
	}
	}
	else
	if(write(STDOUT_FILENO,bufimpar,sizeof(bufimpar)) != sizeof(bufimpar)) {
		perror("\nError en write");
		exit(-1);
	}
	
} else{  //proceso padre ejecutando el programa
	sleep(1);
	if(entero%4==0){
	if(write(STDOUT_FILENO,bufd,sizeof(bufd)) != sizeof(bufd)) {
		perror("\nError en write");
		exit(-1);
	}
	}
else
	if(write(STDOUT_FILENO,bufi,sizeof(bufi)) != sizeof(bufi)) {
		perror("\nError en write");
		exit(-1);
	}
		
}

exit(EXIT_SUCCESS);
}
