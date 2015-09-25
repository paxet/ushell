/*-----------------------------------------------------+      
 |     E J E C U C I O N . C                       |
 +-----------------------------------------------------+
 |     Version    :  4-Julio-2002                      |
 |     Autor      :  Profesorado UPV                   |
 |     Descripcion:                                    |
 +-----------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "defines.h"
#include "redireccion.h"

#define BUFSIZE 1024

CMD cmd;
CMDFD * pipefd;

void construye_orden(char *argv[]);
void filtro(char *nombre);

int main(int argc, char *argv[])
{ 
  int status;

  if (argc !=4 ) {
    fprintf(stderr, "Usage: %s fich_entrada:[nombre | -] fich_salida:[nombre | -] append:[1 | 0] \n", argv[0]);
    exit(1);
  }

  construye_orden(argv);
 
  pipefd=pipeline(&cmd);
  
  if (fork() == 0) { /* CODIGO DEL HIJO */
    if ((*pipefd)[0].infd != STDIN_FILENO)  dup2( (*pipefd)[0].infd, STDIN_FILENO );
    if ((*pipefd)[0].outfd!= STDOUT_FILENO) dup2( (*pipefd)[0].outfd, STDOUT_FILENO );
    fprintf(stderr, "Hijo: fd[entrada]: %d fd[salida]: %d \n", (*pipefd)[0].infd, (*pipefd)[0].outfd);
    cerrar_fd();

    printf("SOY EL HIJO Y DIGO:"); fflush(stdout);
    filtro("Hijo");

    exit(1);
    }

  /* CODIGO DEL PADRE*/
    if ((*pipefd)[1].infd != STDIN_FILENO)  dup2( (*pipefd)[1].infd, STDIN_FILENO );
    if ((*pipefd)[1].outfd!= STDOUT_FILENO) dup2( (*pipefd)[1].outfd, STDOUT_FILENO);
    fprintf(stderr, "Padre: fd[entrada]: %d fd[salida]: %d\n", (*pipefd)[1].infd, (*pipefd)[1].outfd);
    cerrar_fd();

    printf("SOY EL PADRE Y ME HAN ENVIADO: "); fflush(stdout);
    filtro("Padre");

    wait(&status);
    exit(1);
}

void construye_orden(char * argv[])
{ 
  int i,j;

  cmd.num_ordenes=2;
  cmd.num_argumentos[0]=1;
  cmd.num_argumentos[1]=1;
  cmd.es_background= FALSE;

  (strcmp("-",argv[1])==0) ? strcpy(cmd.fich_entrada, "\0") : strcpy(cmd.fich_entrada, argv[1]);
  (strcmp("-",argv[2])==0) ? strcpy(cmd.fich_salida, "\0")  : strcpy(cmd.fich_salida, argv[2]);
  cmd.es_append =( (strcmp("1",argv[3])==0 ) ? TRUE : FALSE);
}

void filtro(char * nombre)
{
  int count;
  char buf[BUFSIZE];

    while ( (count= read(STDIN_FILENO, buf, sizeof(buf))) >0 ) {
      if (write(STDOUT_FILENO, buf, count) != count){ 
        fprintf(stderr, "%s: no pudo leer del escribir en el tubo\n", nombre);
        exit(1);
      }
    }
}
