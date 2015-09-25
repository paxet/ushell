/*-----------------------------------------------------+      

 |     U S H . C                                       |
 +-----------------------------------------------------+
 |     Version    :  4-Julio-2002                      |
 |     Autor      :  Javier Caballero                  |

 |     Descripcion:                                    |
 +-----------------------------------------------------*/
#include "defines.h"
#include "analizador.h"
#include "redireccion.h"
#include "ejecucion.h"
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#define MAX 100

char linea[MAXLINE];
char *milinea;
CMD *micmd;
CMDFD *mifd;
int ayuda=0;
struct sigaction mascara;

char * getlinea(void)
{
    char buf[MAX];
    int ayuda=1;
    //char linea[MAXLINE];
    int i=0;
    int h;
    linea[0]='\0';
    fflush(stdin);
    getcwd(buf, MAX);
    printf("%s%s", buf, PROMPT);
    while(ayuda!='\n'&& ayuda!=EOF) {
       
        ayuda=getchar();
	if(ayuda==EOF) {
	    printf("ush: logout\n\n");
	    exit(0);
	}
	if(i>=MAXLINE) {
	
	    printf("Error, se ha sobrepasado el tamaño maximo de la linea\n\a");
	    break;
	}

       linea[i]=(char)ayuda;
       i++;
        
    }

    linea[i]=(char)'\0';
    //printf("%s",linea);
    return linea;
}

void visualizar(CMD *orden) {

  int j;
  int k;
  printf("Numero de ordenes: %d\n", orden->num_ordenes);
  for(j=0;j<orden->num_ordenes;j++) {
    printf("Orden \"%d\": %s\n",j+1, orden->argumentos[j][0]);
    for(k=1;k<(int)orden->num_argumentos[j];k++) {

	printf("Argumento %d: %s\n", k, orden->argumentos[j][k]);
    }//fin del 2 for
    printf("Numero de argumentos: %d\n", orden->num_argumentos[j]-1);
  }//fin del for
  if(strlen(orden->fich_entrada)==0){
    printf(""); }
  else {
    printf("El fichero de entrada: %s\n", orden->fich_entrada); }
  if(strlen(orden->fich_salida)==0) {
    printf("");}
  else {
    printf("El fichero de salida: %s\n", orden->fich_salida);}
  if(orden->es_background==1)
     printf("La instruccion se ejecuta en background\n");
  if(orden->es_append==1)
     printf("La salida se contatena al fichero: %s\n", orden->fich_salida);

     }//fin del visualizar

void inicializaCMD(CMD * ordenes) {

  ordenes->argumentos[0][0]='\0';
  ordenes->num_ordenes=0;
  ordenes->num_argumentos[0]=0;
  ordenes->fich_entrada[0]='\0';
  ordenes->fich_salida[0]='\0';
  ordenes->es_background=FALSE;
  ordenes->es_append=FALSE;
}

int orden_interna(CMD * ordenes) {
  
  if(strcmp(ordenes->argumentos[0][0], "cd")==0) {
    if(ordenes->num_argumentos[0]==1) {
      chdir(getenv("HOME"));
      return OK;
    }
    else {
      chdir(ordenes->argumentos[0][1]);
      return OK;
    }
  }
  else {
    if(strcmp(ordenes->argumentos[0][0], "exit")==0) {
      exit(0);
      return OK;
    }
    //AQUI DEBERIAMOS SEGUIR PONIENDO IFS PARA CADA INSTRUCCION INTERNA DE USH
    else return ERROR;
  }
}

void no_interactivo(char *linea) {

    mascara.sa_handler=SIG_IGN;
    sigaction(SIGINT, &mascara, NULL);
    sigaction(SIGQUIT, &mascara, NULL);
    sigaction(SIGTTIN, &mascara, NULL);
    sigaction(SIGTTOU, &mascara, NULL);
   
    system("clear");
    fflush(stdin);
    if(strcmp(linea,"\n")==0) exit(0);
    printf("Aquí llega -1, linea= %s\n", linea);
    linea[strlen(linea)]='\n';
    micmd=analizar(linea);
 
    printf("Aquí llega\n");
    if(orden_interna(micmd)==OK) exit(0);
    printf("Aquí llega 2\n");
    visualizar(micmd);
    mifd= pipeline(micmd);
    ayuda=0;
    ayuda= ejecutar(micmd, mifd, &mascara);
    //printf("\nLa instruccion ha devuelto un %d\n", ayuda);
    exit(0);
}

int main(int argc, char * argv[])
{

    /*if(strcmp(argv[1], "-c")==0) {
	no_interactivo(argv[2]);
	exit(0);
    }//fin del if
    else {*/

    if(argc>=2) {
	if(strcmp(argv[1], "-c")==0) {
	    if(argc>2) no_interactivo(argv[2]);
	    else exit(0);
	}
    }
    else {

    mascara.sa_handler=SIG_IGN;
    sigaction(SIGINT, &mascara, NULL);
    sigaction(SIGQUIT, &mascara, NULL);
    sigaction(SIGTTIN, &mascara, NULL);
    sigaction(SIGTTOU, &mascara, NULL);
   
    system("clear");
    while(TRUE) {
    fflush(stdin);
    milinea=getlinea();
    fflush(stdin);
    if(strcmp(milinea,"\n")==0) continue;
    //inicializaCMD(micmd);
    micmd=analizar(milinea);
 
    if(orden_interna(micmd)==OK) continue;
    visualizar(micmd);
    mifd= pipeline(micmd);
    ayuda=0;
    ayuda= ejecutar(micmd, mifd, &mascara);
    //printf("\nLa instruccion ha devuelto un %d\n", ayuda); 

    }//fin del while
    }
  return 0;
}











