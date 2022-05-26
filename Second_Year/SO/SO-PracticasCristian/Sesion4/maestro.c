

#include<sys/types.h>
#include <sys/stat.h>
#include <math.h>
#include <string.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>


int main(int argc, char *argv[]) 
{
int inicio, fin, i;

if(argc<3){
perror("maestro intervaloI intervaloF\n");
return EXIT_FAILURE;
}

inicio=atoi(argv[1]);
fin=atoi(argv[2]);

int fd1[2];
int fd2[2];
int bytes1, bytes2, val1, val2;
pid_t esclavo1, esclavo2;
int intervalos[6];

char ini[10];
char fini[10];

intervalos[0]=inicio;
intervalos[1]=fin;
intervalos[2]=inicio;
intervalos[3]=(inicio+fin)/2 -1;
intervalos[4]=intervalos[3]+1;
intervalos[5]=fin;

pipe(fd1);
pipe(fd2);

printf("\nNUMEROS PRIMOS EN EL INTERVALO [%d,%d]: \n", inicio, fin);

esclavo1=fork();
sprintf(ini,"%d",inicio);
sprintf(fini,"%d",intervalos[3]);
if(esclavo1==0){
close(fd1[0]);
dup2(fd1[1],STDOUT_FILENO);
if(execlp("./esclavo","esclavo",ini,fini,NULL)<0){
perror("\nERROR EN EL EXCL ESCLAVO1\n");
return EXIT_FAILURE;
}
}
else{
close(fd1[1]);
while((bytes1=read(fd1[0],&val1, sizeof(int)))>0){
printf("%d ",val1);
}
close(fd1[0]);
}

esclavo2=fork();
sprintf(ini,"%d",intervalos[4]);
sprintf(fini,"%d",fin);
if(esclavo2==0){
close(fd2[0]);
dup2(fd2[1],STDOUT_FILENO);
if(execlp("./esclavo","esclavo",ini,fini,NULL)<0){
perror("\nERROR EN EL EXCL ESCLAVO2\n");
return EXIT_FAILURE;
}
}
else{
close(fd2[1]);
while((bytes2=read(fd2[0],&val2, sizeof(int)))>0){
printf("%d ",val2);
}
close(fd2[0]);
printf("\n");
}

return 0;

}


