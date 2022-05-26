

#include<sys/types.h>
#include <sys/stat.h>
#include <math.h>
#include <string.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>

int esPrimo(int n){
	int esPrimo=1;
	int k=2;

	while(esPrimo && k<=sqrt(n)){
		if(n%k==0)
			esPrimo=0;
			k++;
	}

	return esPrimo;
}

int main(int argc, char *argv[]) 
{
int inicio, fin, i;

if(argc<3){
perror("esclavo intervaloI intervaloF");
return EXIT_FAILURE;
}



inicio=atoi(argv[1]);
fin=atoi(argv[2]);

for(int i=inicio; i<fin; i++)
if(esPrimo(i))
	write(STDOUT_FILENO,&i, sizeof(int));



return 0;

}


