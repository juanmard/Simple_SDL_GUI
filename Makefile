# Makefile of gui-game


CC = gcc
CPPFLAGS =
CFLAGS = -Wall -Wextra -O3 `pkg-config --cflags sdl2 SDL2_image`
LDFLAGS = -pthread
LDLIBS = `pkg-config --libs sdl2 SDL2_image`

SRC = main.c ssg_button.c ssg_text.c graphic_utils.c
OBJ = ${SRC:.c=.o}

all: main

main: ${OBJ}


.PHONY: clean

clean:
	rm -f main ${OBJ}



# END
