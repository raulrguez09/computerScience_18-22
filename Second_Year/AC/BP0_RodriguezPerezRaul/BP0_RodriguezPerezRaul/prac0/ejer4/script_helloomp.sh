#!/usr/bin/env bash
#Todos los scripts que se hagan para atcgrid deben incluir lo siguiente:
#1. Se asigna al trabajo el nombre helloomp
#PBS -N helloomp
#2. Se asigna el trabajo a la cola ac
#PBS -q ac
#3. Se imprime información del trabajo usando variables de entorno de PBS

#Obtener información de las variables de entorno del sistema de colas:
echo "#########################################################################"
echo "Id. usuario del trabajo: $SLURM_JOB_USER"
echo "Id. del trabajo: $SLURM_JOBID"
echo "Nombre del trabajo especificado por usuario: $SLURM_JOB_NAME"
echo "Directorio de trabajo (en el que se ejecuta el script): $SLURM_SUBMIT_DIR"
echo "Cola: $SLURM_JOB_PARTITION"
echo "Host de envío del trabajo: $SLURM_SUBMIT_HOST"
echo "Nº de nodos asignados al trabajo: $SLURM_JOB_NUM_NODES"
echo "Nodos asignados al trabajo: $SLURM_JOB_NODELIST"
echo "CPUs por nodo: $SLURM_JOB_CPUS_PER_NODE"
echo "#########################################################################"
# FIN del trozo que deben incluir todos los scripts

#Se fija a 12 el nº de threads máximo (tantas como cores en un nodo)
export OMP_THREAD_LIMIT=12
echo "Nº de threads inicial: $OMP_THREAD_LIMIT"
#Se ejecuta HelloOMP que está en el directorio hello con distinto nº de threads

echo "Directorio de trabajo: $SLURM_SUBMIT_DIR"
for ((P=OMP_THREAD_LIMIT;P>0;P=P/2))
do
	export OMP_NUM_THREADS=$P
	echo -e "\n1.Para $OMP_NUM_THREADS threads:"
	$SLURM_SUBMIT_DIR/HelloOMP2
done
