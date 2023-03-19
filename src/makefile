# Name of the project
PROJ_NAME=program
 
# .cc files
C_SOURCE=$(wildcard *.cc)
 
# .h files
H_SOURCE=$(wildcard *.h)
 
# Object files
OBJ=$(C_SOURCE:.cc=.o)
 
# Compiler
CC=g++
 
# Flags for compiler
CC_FLAGS= -g -c -Wall
 
#
# Compilation and linking
#
all: $(PROJ_NAME)
 
$(PROJ_NAME): $(OBJ)
	$(CC) -o $@ $^
 
%.o: %.cc %.h
	$(CC) -o $@ $< $(CC_FLAGS)
 
main.o: main.cc $(H_SOURCE)
	$(CC) -o $@ $< $(CC_FLAGS)
 
clean:
	rm -rf *.o $(PROJ_NAME) *~