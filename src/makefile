OBJS	= cpu.o main_class.o main.o
SOURCE	= cpu.cc main_class.cc main.cc
HEADER	= cpu.h main_class.h traits.h
OUT	= program.o
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

cpu.o: cpu.cc
	$(CC) $(FLAGS) cpu.cc 

main_class.o: main_class.cc
	$(CC) $(FLAGS) main_class.cc 

main.o: main.cc
	$(CC) $(FLAGS) main.cc 


clean:
	rm -f $(OBJS) $(OUT)
