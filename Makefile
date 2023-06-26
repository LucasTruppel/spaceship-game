IDIR = src
LDIR = lib
CC=g++
LDLIBS =  -lsfml-graphics -lsfml-window -lsfml-system -lm  -lpng -g
CFLAGS=-I$(IDIR) -I$(LDIR) -g -Wextra -Wall -w

LDFLAGS= $(CFLAGS)

ODIR = bin
LIBS= $(LDLIBS) $(LDFLAGS)

_SRC_DEPS = window.h game.h window.h spaceship.h enemy_spaceship.h game_handler.h player_spaceship.h shot.h keyboard_handler.h shot_handler.h constants.h
_LIB_DEPS = list.h semaphore.h system.h thread.h traits.h cpu.h debug.h
DEPS = $(patsubst %,$(IDIR)/%,$(_SRC_DEPS)) $(patsubst %,$(LDIR)/%,$(_LIB_DEPS))

_SRC_OBJ = main.o window.o game.o spaceship.o enemy_spaceship.o game_handler.o player_spaceship.o shot.o keyboard_handler.o shot_handler.o constants.o
_LIB_OBJ = cpu.o debug.o semaphore.o system.o thread.o
OBJ = $(patsubst %,$(ODIR)/%,$(_SRC_OBJ)) $(patsubst %,$(ODIR)/%,$(_LIB_OBJ))

$(ODIR)/%.o: $(IDIR)/%.cc $(DEPS)
	$(CC) -std=c++14 -c -o $@ $< $(CFLAGS)

$(ODIR)/%.o: $(LDIR)/%.cc $(DEPS)
	$(CC) -std=c++14 -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -std=c++14 -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ main
