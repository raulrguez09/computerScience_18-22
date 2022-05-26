
#include<sys/types.h>
#include<unistd.h>		
#include<stdio.h>
#include<errno.h>
#include <stdlib.h>
#include <sys/wait.h>
int main ()
{

	int estado;
	int num_hijos = 5;
	pid_t pid;
	
	for (int i = 0; i < num_hijos; i++){
		pid = fork();

		if (pid == 0){ // El hijo imprime y muere
			printf("Soy el hijo con PID %i\n", getpid());
			exit(0);
		}

		estado=pid;

	}

	for(int i = 0; i < num_hijos; i++){
		pid = wait(&estado);
		printf("Ha finalizado el hijo con PID %i\n", pid);
		printf("Solo me quedan %d hijos vivos\n", num_hijos-i-1);
	}
}

