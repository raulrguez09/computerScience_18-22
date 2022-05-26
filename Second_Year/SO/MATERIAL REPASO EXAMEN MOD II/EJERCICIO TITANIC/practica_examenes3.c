#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include <string.h>
#include <ctype.h> //isdigit()
#include <limits.h> //limites como INT_MAX

int main(int argc, char *argv[])
{
    int fd[2];
    pid_t PID;

    pipe(fd);

    if((PID = fork()) <0){
        perror("fork");
        exit(-1);
    }

    if(PID == 0){
        close(fd[0]);
        if (dup2(fd[1],STDOUT_FILENO) <0){
            perror("Error en el write \n");
            exit(EXIT_FAILURE);
        }
        execlp("cut","cut", "-d", ";", "-f", "6", "titanic.csv", NULL);
        perror("Error en ejecutando comando\n");
    }
    else{
        close(fd[1]);

        char buf[2];
        char c[2];
        int edad;
        int sum_edades=0;
        int total=0;
        int min=INT_MAX; //2147483647
        int max=INT_MIN; //(-2147483647-1)
        int men_5=0;
        char numero[4]="";


        while (read(fd[0], buf, 1)) {
            if (strcmp(buf, "\n")) { //si no es \n
                sprintf(numero, "%s%s", numero, buf); //concatenando digitos de la edad
            }
            else { //es \n, ya hemos leido los dígitos de la edad
                edad = atoi(numero);
                strcpy(numero, ""); //reinicializamos nuestra variable numero de nuevo, para volver a concatenar los digitos

                if (edad > max) max = edad;
                if (edad < min) min = edad;
                if (edad < 5)   men_5++;
                sum_edades += edad;
                total++;
            }
        }

        // guardar en un fichero el resultado anterior
        char contenido[200];
        sprintf(contenido, "Total personas: %d\nMedia edad: %f\nMás joven: %d\nMás mayor: %d\nMenores de 5 años: %d\n", total, sum_edades/total*1.0f, min, max, men_5);
        int fd = open("resultado_titanic.txt", O_CREAT|O_TRUNC|O_WRONLY, 0770);
        if(write(fd, contenido, strlen(contenido))<0){
            perror("Error en el write \n");
            exit(EXIT_FAILURE);
        }
        close(fd);
    }

    return(0);
}
