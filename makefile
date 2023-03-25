# Nome do projeto
PROJ_NAME=program

# Arquivos .cc
CC_SOURCE=$(wildcard ./src/*.cc)

# Arquivos .h
H_SOURCE=$(wildcard ./src/*.h)

# Arquivos objeto
OBJ=$(subst .cc,.o,$(subst src,bin,$(CC_SOURCE)))

# Compilador
CC=g++

# Flags para o compilador
CC_FLAGS= -g -c -Wall

# Compilação
all: $(PROJ_NAME)

$(PROJ_NAME): $(OBJ)
	$(CC) $^ -o $@

./bin/%.o: ./src/%.cc ./src/%.h
	$(CC) $< $(CC_FLAGS) -o $@

./bin/main.o: ./src/main.cc $(H_SOURCE)
	$(CC) $< $(CC_FLAGS) -o $@

clean:
	@ rm -rf ./bin/*.o $(PROJ_NAME) *~

.PROG: all clean