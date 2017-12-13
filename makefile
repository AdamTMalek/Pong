CC = gcc

COMPILER_FLAGS = -g -pedantic -Wall
LINKER_FLAGS = -lSDL2 -lSDL2_ttf -lm

OBJ =\
	src/main.o \
	src/map.o \
	src/window.o \
	src/path.o \
	src/score.o \
	src/game.o \

all: main

main: $(OBJ)
	$(CC) $(COMPILER_FLAGS) $(OBJ) $(LINKER_FLAGS) -o build/pong

clean:
	rm -f build/*.o pong