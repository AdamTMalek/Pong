CC = gcc

COMPILER_FLAGS = -g -pedantic -Wall
LINKER_FLAGS = -lSDL2 -lSDL2_ttf -lSDL2_mixer -lm

OBJ =\
	build/main.o \
	build/map.o \
	build/window.o \
	build/path.o \
	build/score.o \
	build/game.o \
	build/sound.o

$(OBJ): build/%.o: src/%.c
	$(CC) -c $< -o $@

all: main

main: $(OBJ)
	$(CC) $(COMPILER_FLAGS) $(OBJ) $(LINKER_FLAGS) -g -o build/pong

clean:
	rm -f build/*.o build/pong
