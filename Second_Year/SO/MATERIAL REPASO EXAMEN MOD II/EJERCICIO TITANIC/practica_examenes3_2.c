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

//Implementar: cat titanic.csv | cut -d";" -f 6

int main(int argc, char *argv[])
{
    int fd_cat[2], fd_cut[2];
    pid_t PID;

    pipe(fd_cat);

    if((PID = fork()) <0){
        perror("fork");
        exit(-1);
    }

    if(PID == 0){
        close(fd_cat[0]);

       dup2(fd_cat[1],STDOUT_FILENO);
        execlp("cat","cat", "titanic.csv", NULL);
        perror("Error en ejecutando comando\n");
    }
    else{
        close(fd_cat[1]);

        pipe(fd_cut);

        if((PID = fork()) <0){
            perror("fork");
            exit(-1);
        }

        if(PID == 0){
            close(fd_cut[0]);

            dup2(fd_cat[0], STDIN_FILENO); //el resultado de cat titanic.csv lo redirigimos a la entrada de cut
            dup2(fd_cut[1], STDOUT_FILENO); // vamos a escribir el resultado de cat titanic.csv | cut -d";" -f 6 en la salida estandar

            execlp("cut","cut", "-d", ";", "-f", "6", NULL);
            perror("Error en ejecutando comando\n");
        }
        else{
            close(fd_cut[1]);

            char buf[2];
            int edad;
            int sum_edades=0;
            int total=0;
            int min=INT_MAX; //2147483647
            int max=INT_MIN; //(-2147483647-1)
            int men_5=0;
            char numero[4]="";

//            char buf2[100];
//            read(fd_cut[0], buf2, 10);
//            printf("%s", buf2);

            while (read(fd_cut[0], buf, 1)) {
//                printf("%s\n", buf);
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
            int fd = open("resultado_titanic_2.txt", O_CREAT|O_TRUNC|O_WRONLY, 0770);
            if(write(fd, contenido, strlen(contenido))<0){
                perror("Error en el write \n");
                exit(EXIT_FAILURE);
            }
            close(fd);
        }
    }

    return(0);
}
