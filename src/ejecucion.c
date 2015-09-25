/*-----------------------------------------------------+      
 |     E J E C U C I O N . C                           |
 +-----------------------------------------------------+
 |     Version    :  4-Julio-2002                      |
 |     Autor      :  Profesorado UPV                   |
 |     Descripcion:                                    |
 +-----------------------------------------------------*/
#include "defines.h"
#include "redireccion.h"
#include "ejecucion.h"


int status=11111; //inicializado a cualquier numero
int pids[MAXARG]; //guarda los pids de los hijos

int ejecutar(CMD * ordenes, CMDFD *pipefd, struct sigaction *mascara)
{
    int num_ordenes, i, pidhijo=0;
    num_ordenes=ordenes->num_ordenes;
	for(i=0;i<num_ordenes;i++) {
	    pidhijo= fork();
	    if(pidhijo==0) break; //el hijo salta del bucle
	    pids[i]=pidhijo;

	}//fin del for 
	pids[i]='\n';

	if(pidhijo==0) {  //lo ejecuta cada hijo

	  if(ordenes->es_background==TRUE) {
	    mascara->sa_handler=SIG_IGN;
	    sigemptyset(&mascara->sa_mask);
	    mascara->sa_flags=0;
	    sigaction(SIGINT, mascara, NULL);
	    sigaction(SIGQUIT, mascara, NULL);
	  }
	  else {
	    mascara->sa_handler=SIG_DFL;
	    sigemptyset(&mascara->sa_mask);
	    mascara->sa_flags=0;
	    sigaction(SIGINT, mascara, NULL);
	    sigaction(SIGQUIT, mascara, NULL);
	    sigaction(SIGHUP, mascara, NULL);
	    sigaction(SIGABRT, mascara, NULL);
	    sigaction(SIGPIPE, mascara, NULL);
	    sigaction(SIGALRM, mascara, NULL);
	    sigaction(SIGTERM, mascara, NULL);
	  }

	    if((*pipefd)[i].infd!=STDIN_FILENO) dup2((*pipefd)[i].infd, STDIN_FILENO);
	    if((*pipefd)[i].outfd!=STDOUT_FILENO) dup2((*pipefd)[i].outfd, STDOUT_FILENO);
	    cerrar_fd();
	    execvp(ordenes->argumentos[i][0], ordenes->argumentos[i]);
	    fprintf(stderr, "%s Imposible ejecutar la instruccion, no se encuentra el ejecutable\n",ordenes->argumentos[i][0] );
	    //kill(getpid(), SIGINT);
		return ERROR;

	}//fin del if

	else {		//lo ejecuta el USH
	  cerrar_fd();
	  if(ordenes->es_background==0) {
	      /*for(i=0;i<num_ordenes;i++) {
		waitpid(pids[i], &status, 0);
	    }*/
	    while(wait(NULL)!=pidhijo){
	    }
	  }
	  if(ordenes->es_background==TRUE) {
	    for(i=0;i<num_ordenes;i++) {
		waitpid(pids[i], &status, WNOHANG);
	    }
	      //printf("Terminado\t%s\n", ordenes->argumentos[i-1][0]);
	  }

	  if(WIFEXITED(status)==0){
	      return ERROR;}

	    else {
	      return OK;}

	}//fin del else
    return OK;
}//fin del ejecutar
