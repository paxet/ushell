all: 	    ush ejecucion1 ejecucion2 usleep
ejecucion1: redireccion.o ejecucion1.o
ejecucion2: redireccion.o ejecucion2.o

CFLAGS = -D_INTERNAS -D_NO_INTERACTIVO
ush:    ush.c defines.h analizador.h redireccion.h ejecucion.h analizador.o redireccion.o ejecucion.o
	gcc $(CFLAGS) ush.c analizador.o redireccion.o ejecucion.o -o ush
	strip ush

analizador.o:   analizador.c defines.h analizador.h
	gcc -c $(CFLAGS) analizador.c

redireccion.o:  redireccion.c defines.h redireccion.h
	gcc -c $(CFLAGS) redireccion.c

ejecucion.o:    ejecucion.c defines.h  ejecucion.h
	gcc -c $(CFLAGS) ejecucion.c

ejecucion1.o:   ejecucion1.c defines.h redireccion.h
	gcc -c $(CFLAGS) ejecucion1.c

ejecucion2.o:   ejecucion2.c defines.h redireccion.h
	gcc -c $(CFLAGS) ejecucion2.c

usleep.o:       ../lib/usleep.c
	gcc -c $(CFLAGS) ../lib/usleep.c

clean:
	rm *.o ush ejecucion1 ejecucion2 usleep
	rm -rf dkko mon

