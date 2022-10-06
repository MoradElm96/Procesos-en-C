#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>


int main(){

    int fd[2];
    char cadena[]="italia es uno de los paises del continente europeo";
    char buffer[30];

    pid_t pid;

    pipe(fd);

    pid=fork();


   switch(pid){

       case -1: // error

        printf("error porque NO se ha podido hacer el fork \n");

        return -1;

        break;

       case 0: //hijo 1

        // Escribimos en el pipe

        printf("soy el proceso %d hijo 1 de %d\n",getpid(),getppid());

        printf("El hijo 1 escribe en el pipe: %s\n",cadena);

        write(fd[1],cadena,strlen(cadena));

        break;

       default: //padre

        pid=fork();

        if(pid==0){ //hijo 2

            close(fd[1]);

            printf("soy el proceso %d hijo 2 de %d\n",getpid(),getppid());

            // Leemos del pipe

            read(fd[0], buffer, sizeof(buffer));

            for(int i =0; i <= strlen(cadena); ++i){

                if(buffer[i]=='i'){

                    buffer[i]='1';

                }else if(buffer[i]=='s'){

                    buffer[i]='5';
                 } 
            }

            printf("El hijo 2 lee del pipe: %s\n", buffer);

        }else if(pid==-1){

            printf("error porque NO se ha podido hacer el fork \n");

        return -1; }

        wait(NULL);

        break; 

    }

return 0; 

}
