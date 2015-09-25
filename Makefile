IDIR = include
LDIR = lib
SDIR = src
CFLAGS = -D_INTERNAS -D_NO_INTERACTIVO -I$(IDIR) -Wall
OBJS = analizador.o redireccion.o ejecucion.o

all:        ush ejecucion1 ejecucion2 usleep
ejecucion1: redireccion.o ejecucion1.o
ejecucion2: redireccion.o ejecucion2.o

ush:    $(SDIR)/ush.c $(IDIR)/defines.h $(IDIR)/analizador.h $(IDIR)/redireccion.h $(IDIR)/ejecucion.h $(OBJS)
	gcc $(CFLAGS) $(SDIR)/ush.c $(OBJS) -o ush
	strip ush

analizador.o:   $(SDIR)/analizador.c $(IDIR)/defines.h $(IDIR)/analizador.h
	gcc -c $(CFLAGS) $(SDIR)/analizador.c

redireccion.o:  $(SDIR)/redireccion.c $(IDIR)/defines.h $(IDIR)/redireccion.h
	gcc -c $(CFLAGS) $(SDIR)/redireccion.c

ejecucion.o:    $(SDIR)/ejecucion.c $(IDIR)/defines.h  $(IDIR)/ejecucion.h
	gcc -c $(CFLAGS) $(SDIR)/ejecucion.c

ejecucion1.o:   $(SDIR)/ejecucion1.c $(IDIR)/defines.h $(IDIR)/redireccion.h
	gcc -c $(CFLAGS) $(SDIR)/ejecucion1.c

ejecucion2.o:   $(SDIR)/ejecucion2.c $(IDIR)/defines.h $(IDIR)/redireccion.h
	gcc -c $(CFLAGS) $(SDIR)/ejecucion2.c

usleep.o:       $(LDIR)/usleep.c
	gcc -c $(CFLAGS) $(LDIR)/usleep.c

clean:
	rm *.o ush ejecucion1 ejecucion2 usleep
	rm -rf dkko mon

