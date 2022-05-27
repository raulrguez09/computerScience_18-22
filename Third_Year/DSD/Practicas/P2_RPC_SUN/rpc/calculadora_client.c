/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "calculadora.h"


void
calculadora_prog_1(char *host, float a, char oper, float b)
{
	CLIENT *clnt;
	int  *result_1;
	int  *result_2;
	int  *result_3;
	int  *result_4;

#ifndef	DEBUG
	clnt = clnt_create (host, CALCULADORA_PROG, CALCULADORA_VER, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	switch (oper)
	{
		case '+':
			result_1 = sumar_1(a, b, clnt);
			printf("El resultado de la suma es: %d\n",*result_1 );
			if (result_1 == (int *) NULL) {
				clnt_perror (clnt, "call failed");
			}
		break;

		case '-':
			result_2 = restar_1(a, b, clnt);
			printf("El resultado de la resta es: %d\n",*result_2 );
			if (result_2 == (int *) NULL) {
				clnt_perror (clnt, "call failed");
			}
		break;

		case '/':
			result_3 = dividir_1(a, b, clnt);
			printf("El resultado de la divicion es: %d\n",*result_3);
			if (result_3 == (int *) NULL) {
				clnt_perror (clnt, "call failed");
			}
		break;

		case '*':
			result_4 = multiplicar_1(a, b, clnt);
			printf("El resultado de la multiplicacion es: %d\n",*result_4 );
			if (result_4 == (int *) NULL) {
				clnt_perror (clnt, "call failed");
			}
		break;
	}
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


int
main (int argc, char *argv[])
{
	char *host;
	float a, b;
	char oper;

	if (argc != 5) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}

	host = argv[1];
	a = atof(argv[2]);
	oper = *argv[3];
	printf("La operación es: %c", oper);
	b = atof(argv[4]);

	calculadora_prog_1 (host, a, oper, b);
exit (0);
}