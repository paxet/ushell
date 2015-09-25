/*----------------------------------------------------+
|     U S L E E P . C                                 |
+-----------------------------------------------------+
|     Version    :  25-Septiembre-2015                |
|     Autor      :  Javier Caballero                  |
|     Descripcion:                                    |
+-----------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  int status, fd[2];

  if (argc !=2 ) {
    fprintf(stderr, "Usage: %s microseconds:[us | -] \n", argv[0]);
    exit(1);
  }
  usleep(atoi(argv[1]));
}
