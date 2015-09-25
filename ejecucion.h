/*-----------------------------------------------------+      
 |     E J E C U C I O N . C                           |
 +-----------------------------------------------------+
 |     Version    :  4-Julio-2002                      |
 |     Autor      :  Javier Caballero                  |
 |     Descripcion:                                    |
 +-----------------------------------------------------*/
#ifndef EJECUCION_H
#define EJECUCION_H

/*******************************************************************/
/*                        ejecutar                                 */
/*-----------------------------------------------------------------*/
/* Crea los procesos para ejecutar "ordenes" en tuberia y redirige */
/* la STD_INPUT y STD_OUTPUT de un proceso hacia/desde "pipefd"    */          
/* ENTRADA: una orden analizada "ordenes" y los descriptores       */
/* "pipefd" de la tuberia                                          */
/* SALIDA: OK o ERROR                                              */ 
/*******************************************************************/
extern int ejecutar (CMD * ordenes, CMDFD * pipefd, struct sigaction *mascara);

#endif

