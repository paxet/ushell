/*-----------------------------------------------------+      

 |     D E F I N E S . H                               |
 +-----------------------------------------------------+
 |     Version    :  4-Julio-2002                      |
 |     Autor      :  Javier Caballero                  |

 |     Descripcion:                                    |
 +-----------------------------------------------------*/

#ifndef DEFINES_H
#define DEFINES_H

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

#define max(a,b) (((a)>(b)) ? (a): (b))

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0

#define LOGO "MICRO SHELL  (c)2003 Greven il-Vec, el Vizjerei\n"
#define PROMPT " : ush_$ "

#define MAXLINE 200
#define MAXARG 20
#define PIPELINE 10
#define MAXNAME 100

typedef struct
{
  char * argumentos[PIPELINE][MAXARG];
  int num_ordenes;
  int num_argumentos[PIPELINE];
  char fich_entrada[MAXNAME+1];
  char fich_salida[MAXNAME+1];
  int es_background;
  int es_append;
} CMD;

typedef struct
{
  int infd;
  int outfd;
}CMDFD[PIPELINE-1];


#endif

