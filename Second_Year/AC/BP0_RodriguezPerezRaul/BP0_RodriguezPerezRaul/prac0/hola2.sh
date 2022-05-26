#!/usr/bin/env bash

#Órdenes para el sistema de colas:
#1. Asigna al trabajo un nombre
#SBATCH --job-name=hola2
#2. Asigna el trabajo a una cola (partición)
#SBATCH --partition=ac
#3. Asigna el trabajo aun cuenta (account)
#SBATCH --account=ac

#Obtener información de las variables de entorno del sistema de colas:
echo "#########################################################################"
echo "Id. usuario del trabajo: $SLURM_JOB_USER"
echo "Id. del trabajo: $SLURM_JOBID"
echo "Nombre del trabajo especificado por usuario: $SLURM_JOB_NAME"
echo "Directorio de trabajo (en el que se ejecuta el script): $SLURM_SUBMIT_DIR"
echo "Cola: $SLURM_JOB_PARTITION"
echo "Host de envío del trabajo:$SLURM_SUBMIT_HOST"
echo "Nº de nodos asignados al trabajo: $SLURM_JOB_NUM_NODES"
echo "Nodos asignados al trabajo: $SLURM_JOB_NODELIST"
echo "CPUs por nodo: $SLURM_JOB_CPUS_PER_NODE"
echo "#########################################################################"

#Instrucciones del script para ejecutar código:
echo "1. Ejecución hola2.sh una vez sin cambiar nº de hebras (valor por defecto):"
srun ./hola2

echo "2. Ejecución hola2.sh varias veces con distinto nº de hebras:"
for (( i=12; i>0; i=i/2 )); do
	echo "-------------------------- $i hebras -------------------------------"
	export OMP_NUM_THREADS=$i
	srun ./hola2
done

