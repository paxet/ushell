/*-----------------------------------------------------+      
 |     R E D I R E C C I O N . C                       |
 +-----------------------------------------------------+
 |     Version    :  4-Julio-2002                      |
 |     Autor      :  Javier Caballero                  |
 |     Descripcion:                                    |
 +-----------------------------------------------------*/
#include "defines.h"
#include "analizador.h"
#include "redireccion.h"


CMDFD micmdfd;
int num_ordenes;
CMD *puntero;

void redireccion_ini();
int cerrar_fd(void);
int r_entrada(char *fichero);
int r_salida(char *fichero2);

CMDFD * pipeline(CMD * ordenes)
{
    int i, filedes[2];
    puntero=ordenes;
    redireccion_ini();
    num_ordenes=ordenes->num_ordenes;
    if(strcmp(ordenes->fich_entrada, "")!=0) micmdfd[0].infd= r_entrada(ordenes->fich_entrada);
    if(strcmp(ordenes->fich_salida, "")!=0) micmdfd[num_ordenes-1].outfd= r_salida(ordenes->fich_salida);
    if(strcmp(ordenes->fich_entrada, "") && ordenes->es_background) micmdfd[0].infd=(long)"/dev/null";
    for(i=0;i<num_ordenes-1;i++) {
	pipe(filedes);
	if(micmdfd[i+1].infd==0) micmdfd[i+1].infd=filedes[0];
	if(micmdfd[i].outfd==1)micmdfd[i].outfd=filedes[1];
	//return &micmdfd;
    }//fin del for
    return &micmdfd;
} /* pipeline */

void redireccion_ini() {
    int i;
    for(i=0;i<PIPELINE;i++) {
	micmdfd[i].infd=0;
	micmdfd[i].outfd=1;
    }//fin del for

}

int cerrar_fd(void)
{
    int i;
    for(i=0; i<num_ordenes;i++) {
	if(micmdfd[i].infd!=0) close(micmdfd[i].infd);
	if(micmdfd[i].outfd!=1) close(micmdfd[i].outfd);
    }//fin del for
    return 0;
}


int r_entrada(char *fichero){

    int mifd;
    mifd=open(fichero,O_RDONLY);

    return mifd;

}//fin de r_entrada

int r_salida(char *fichero2) {

    int mifd2;
    if(puntero->es_append)
      mifd2= open(fichero2, O_CREAT | O_APPEND | O_WRONLY, 00664);
    else 
    mifd2=open(fichero2, O_CREAT | O_TRUNC | O_WRONLY, 00664);

    return mifd2;

}//fin de r_salida
