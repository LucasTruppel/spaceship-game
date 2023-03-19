PROJ_NAME=program
 
C_SOURCE=$(wildcard *.cc)
 
H_SOURCE=$(wildcard *.h)
 
OBJ=$(C_SOURCE:.cc=.o)
 
CC=g++
 
CC_FLAGS= -g -c -Wall
 
#Compilation
all: $(PROJ_NAME)
 
$(PROJ_NAME): $(OBJ)
	$(CC) -o $@ $^
 
%.o: %.cc %.h
	$(CC) -o $@ $< $(CC_FLAGS)
 
main.o: main.cc $(H_SOURCE)
	$(CC) -o $@ $< $(CC_FLAGS)
 
clean:
	rm -rf *.o $(PROJ_NAME) *~