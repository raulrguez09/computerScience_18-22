#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>


int main(){
/*
Jerarquía de procesos tipo 1
*/

pid_t childpid;
for (int i=1; i < 20; i++) {
if ((childpid= fork()) == -1) {
fprintf(stderr, "Could not create child %d: %s\n",i,strerror(errno));
exit(-1);
}

printf("Identificador de proceso: %d\n", getpid());
printf("Identificador del proceso padre: %d\n", getppid());

if (childpid)
break;
}
/*
Jerarquía de procesos tipo 2
*/
for (int i=1; i < 20; i++) {
if ((childpid= fork()) == -1) {
fprintf(stderr, "Could not create child %d: %s\n",i,strerror(errno));
exit(-1);
}

if (!childpid)
break;
}
}
