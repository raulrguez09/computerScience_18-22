/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include <memory.h> /* for memset */
#include "vectores.h"

/* Default timeout can be changed using clnt_control() */
static struct timeval TIMEOUT = { 25, 0 };

miVector *
sumar_1(miVector arg1, miVector arg2,  CLIENT *clnt)
{
	sumar_1_argument arg;
	static miVector clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	arg.arg1 = arg1;
	arg.arg2 = arg2;
	if (clnt_call (clnt, SUMAR, (xdrproc_t) xdr_sumar_1_argument, (caddr_t) &arg,
		(xdrproc_t) xdr_miVector, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

miVector *
restar_1(miVector arg1, miVector arg2,  CLIENT *clnt)
{
	restar_1_argument arg;
	static miVector clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	arg.arg1 = arg1;
	arg.arg2 = arg2;
	if (clnt_call (clnt, RESTAR, (xdrproc_t) xdr_restar_1_argument, (caddr_t) &arg,
		(xdrproc_t) xdr_miVector, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

miVector *
dividir_1(miVector arg1, miVector arg2,  CLIENT *clnt)
{
	dividir_1_argument arg;
	static miVector clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	arg.arg1 = arg1;
	arg.arg2 = arg2;
	if (clnt_call (clnt, DIVIDIR, (xdrproc_t) xdr_dividir_1_argument, (caddr_t) &arg,
		(xdrproc_t) xdr_miVector, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}

miVector *
multiplicar_1(miVector arg1, miVector arg2,  CLIENT *clnt)
{
	multiplicar_1_argument arg;
	static miVector clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	arg.arg1 = arg1;
	arg.arg2 = arg2;
	if (clnt_call (clnt, MULTIPLICAR, (xdrproc_t) xdr_multiplicar_1_argument, (caddr_t) &arg,
		(xdrproc_t) xdr_miVector, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}
