#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include <string.h>
int main(int argc, char *argv[]){
pid_t pid;
int estado;
if(!strcmp(argv[1],"bg")){
	if( (pid=fork())<0) {
	perror("\nError en el fork");
	exit(-1);
	}
	else if(pid==0) { //proceso hijo ejecutando el programa
	printf("\nEJECUTANDO PROGRAMA EN BACKGROUND");
		if(execl("/home/cristian/Escritorio/UNI/SO/PRÁCTICAS/SO-P-Todos_MaterialModulo2/Sesion2/ejecutar","ejecutar","/home/cristian/Escritorio/UNI/SO/PRÁCTICAS/SO-P-Todos_MaterialModulo2/Sesion7","7666",NULL)<0) {
		perror("\nError en el execl BG");
		exit(-1);
		}
		
	}
wait(&estado);
printf("\nMi hijo %d ha finalizado con el estado %d\n",pid,estado>>8);
exit(0);

}
else {
	printf("\nEJECUTANDO PROGRAMA EN PRIMER PLANO");
	if(execl("/home/cristian/Escritorio/UNI/SO/PRÁCTICAS/SO-P-Todos_MaterialModulo2/Sesion2/ejecutar","ejecutar","/home/cristian/Escritorio/UNI/SO/PRÁCTICAS/SO-P-Todos_MaterialModulo2/Sesion7","7777",NULL)<0){
	perror("\nERROR EN EL EXECL FG");
	exit(-1);
	}

	exit(0); //CÓMO SE EJECUTA EN PRIMER PLANO???
	
}
}
