IDIR =.
CC=g++
LDLIBS =  -lsfml-graphics -lsfml-window -lsfml-system -lm  -lpng -g
CFLAGS=-I$(IDIR) -g -Wextra -Wall

LDFLAGS= $(CFLAGS)

ODIR=.
LIBS= $(LDLIBS) $(LDFLAGS)

_DEPS = window.h cpu.h debug.h game.h list.h semaphore.h system.h thread.h traits.h window.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o window.o cpu.o debug.o game.o semaphore.o system.o thread.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -std=c++14 -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -std=c++14 -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ main
