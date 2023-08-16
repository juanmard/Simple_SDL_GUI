# Makefile of gui-game


CC = gcc -fsanitize=address
CPPFLAGS =
CFLAGS = -Wall -Wextra -O3 `pkg-config --cflags sdl2 SDL2_image`
LDFLAGS = -pthread
LDLIBS = `pkg-config --libs sdl2 SDL2_image`

SRC = main.c ssg_button.c ssg_text.c graphic_utils.c ssg_menu.c \
	welcome.c my_str.c ssg_menu_list.c hall.c ssg_debug_text.c
OBJ = ${SRC:.c=.o}

all: main

main: ${OBJ}


.PHONY: clean

clean:
	rm -f main ${OBJ}



# END
