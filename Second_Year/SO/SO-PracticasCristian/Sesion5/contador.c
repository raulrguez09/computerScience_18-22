/*
 reciboSignal.c
 Trabajo con llamadas al sistema del Subsistema de Procesos conforme a POSIX 2.10
 Utilizaci—n de la llamada sigaction para cambiar el comportamiento del proceso       
 frente a la recepci—n de una se–al.
*/

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>
#include <stdlib.h>

int cont1=0, cont2=0, cont3=0, cont4=0, cont5=0, cont6=0, cont7=0, cont8=0, cont10=0, cont11=0, cont12=0, cont13=0, cont14=0, cont15=0, cont16=0, cont17=0, cont18=0;

static void handler(int sigNum)
  {


	switch(sigNum){
	case 1: 
		cont1++;
    		printf("\nLa señal 1 se ha recibido %d veces\n\n",cont1); break;
	case 2: 
		cont2++;
    		printf("\nLa señal 2 se ha recibido %d veces\n\n",cont2); break;
	case 3: 
		cont3++;
    		printf("\nLa señal 3 se ha recibido %d veces\n\n",cont3); break;
	case 4: 
		cont4++;
    		printf("\nLa señal 4 se ha recibido %d veces\n\n",cont4); break;
	case 5: 
		cont5++;
    		printf("\nLa señal 5 se ha recibido %d veces\n\n",cont5); break;
	case 6: 
		cont6++;
    		printf("\nLa señal 6 se ha recibido %d veces\n\n",cont6); break;
	case 7: 
		cont7++;
    		printf("\nLa señal 7 se ha recibido %d veces\n\n",cont7); break;
	case 8: 
		cont8++;
    		printf("\nLa señal 8 se ha recibido %d veces\n\n",cont8); break;
	case 10: 
		cont10++;
    		printf("\nLa señal 10 se ha recibido %d veces\n\n",cont10); break;
	case 11: 
		cont11++;
    		printf("\nLa señal 11 se ha recibido %d veces\n\n",cont11); break;
	case 12: 
		cont12++;
    		printf("\nLa señal 12 se ha recibido %d veces\n\n",cont12); break;
	case 13: 
		cont13++;
    		printf("\nLa señal 13 se ha recibido %d veces\n\n",cont13); break;
	case 14: 
		cont14++;
    		printf("\nLa señal 14 se ha recibido %d veces\n\n",cont14); break;
	case 15: 
		cont15++;
    		printf("\nLa señal 15 se ha recibido %d veces\n\n",cont15); break;
	case 16: 
		cont16++;
    		printf("\nLa señal 16 se ha recibido %d veces\n\n",cont16); break;
	case 17: 
		cont17++;
    		printf("\nLa señal 17 se ha recibido %d veces\n\n",cont17); break;
	case 18: 
		cont18++;
    		printf("\nLa señal 18 se ha recibido %d veces\n\n",cont18); break;
	default:
		printf("\nEspecificación de señal invalida\n\n"); break;
	
	}

   }

int main(int argc, char *argv[])
   {
    struct sigaction sa;
sa.sa_handler=handler;
sigemptyset(&sa.sa_mask);

sa.sa_flags=SA_RESTART;
  


for (int i=1; i<=60; i++){
if(sigaction(i,&sa,NULL)==-1){
printf("error en el manejador");}}
while(1);
}


