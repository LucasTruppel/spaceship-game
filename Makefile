IDIR = src
CC=g++
LDLIBS =  -lsfml-graphics -lsfml-window -lsfml-system -lm  -lpng -g
CFLAGS=-I$(IDIR) -g -Wextra -Wall -w

LDFLAGS= $(CFLAGS)

ODIR = bin
LIBS= $(LDLIBS) $(LDFLAGS)

_DEPS = window.h cpu.h debug.h game.h list.h semaphore.h system.h thread.h traits.h window.h collision_handler.h spaceship.h enemy_spaceship.h game_handler.h player_spaceship.h shot.h keyboard_handler.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o window.o cpu.o debug.o game.o semaphore.o system.o thread.o collision_handler.o spaceship.o enemy_spaceship.o game_handler.o player_spaceship.o shot.o keyboard_handler.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(IDIR)/%.cc $(DEPS)
	$(CC) -std=c++14 -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -std=c++14 -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ main
