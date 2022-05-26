#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
int main(int argc, char ** argv)
{
	int *v1, *v2, *v3;
	int i, j, k, l;
	if(argc < 2){
		fprintf(stderr, "\n[ERROR] - Falta el numero de elementos. \n");
		exit(-1);
	}
	unsigned int N = atoi(argv[1]);
	v1 = malloc(N*sizeof(int));
	v2 = malloc(N*sizeof(int));
	v3 = malloc(N*sizeof(int));
	double tiempo_inicio, tiempo_final, tiempo_total;
	#pragma omp parallel
	{
		#pragma omp sections
		{
		#pragma omp section
		for(i=0 ; i<(N/4) ; i++){
			v1[i] = i;
			v2[i] = i;
		}
		#pragma omp section
		for(j=(N/4); j < (N/4)*2; j++){
			v1[j] = j;
			v2[j] = j;
		}
		#pragma omp section 
		for(k=(N/4)*2; k < (N/4)*3; k++){
			v1[k]=k;
			v2[k]=k;
		}
		
		#pragma omp section
		for(l = (N/4)*3; l < N; l++){
			v1[l] = l;
			v2[l] = l;
		}
		}

		#pragma omp single
	tiempo_inicio = omp_get_wtime();

	#pragma omp sections
	{
		#pragma omp section
		for(i = 0; i<(N/4); i++){
			v3[i] = v1[i] + v2[i];
		}
		#pragma omp section
		for(k = (N/4)*2; k < (N/4)*3; k++){
			v3[k] = v1[k] + v2[k];
		}
		#pragma omp section
		for(l = (N/4)*3; l < N; l++){
			v3[l] = v1[l] + v2[l];
		}
	}
	#pragma omp single
	tiempo_final = omp_get_wtime();
	}
	tiempo_total = tiempo_final - tiempo_inicio;
	printf("\nVector 1: ");
	for(i=0; i<N; i++)
	printf("%d\n", v1[i]);
	printf("\nVector 2: ");
	for(i=0; i<N; i++)
	printf("%d\n", v2[i]);
	printf("\nVector del resultado: ");
	for(i=0; i<N; i++)
		printf("%d\n", v3[i]);
	printf("\nEl tiempo en realizar la suma ha sido %f\n",
	tiempo_total);
	exit(0);

}
