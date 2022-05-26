#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>

#define S_ISREG2(mode) ( (mode & S_IFMT) == S_IFREG)

int main(int argc, char *argv[])
{
struct stat atributos;
char tipoArchivo[30];
if(lstat(argv[1],&atributos) < 0) {
printf("\nError al intentar acceder a los atributos de %s",argv[1]);
perror("\nError en lstat");
}

if(S_ISREG2(atributos.st_mode)){
strcpy(tipoArchivo,"Regular");
printf("%s\n",tipoArchivo);
}
else 
	printf("NO ES ARCHIVO REGULAR\n");

return 0;
}
