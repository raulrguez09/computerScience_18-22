/* compilar con: gcc -fopenmp -O2 -Wall hola.c -o hola */

#include <stdio.h>
#include <omp.h>

int main(void)
{
	#pragma omp parallel
	{
		printf("%d: ¡hola!\n", omp_get_thread_num());
		printf("%d: ¡mundo!\n", omp_get_thread_num());
	}
}
