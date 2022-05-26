/* compilar con: gcc -fopenmp -O2 -Wall hola.c -o hola */

#include <stdio.h>
#include <omp.h>

int main(void)
{
	#pragma omp parallel
	printf("%d: ¡hola mundo!\n", omp_get_thread_num());
}

