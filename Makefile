# Makefile of gui-game

CC = gcc
CPPFLAGS = -Iinclude
CFLAGS = -Wall -Wextra -O3 `pkg-config --cflags sdl2 SDL2_image` -g \
		 -fsanitize=address
LDFLAGS = -pthread
LDLIBS = `pkg-config --libs sdl2 SDL2_image` -fsanitize=address

SRC = main.c \
	  src/ssg_basic.c \
	  src/ssg_slider.c \
	  src/ssg_component.c \
	  src/ssg_components_list.c \
	  src/ssg_button.c src/ssg_text.c src/graphic_utils.c \
	  src/ssg_menu.c src/welcome.c src/my_str.c src/ssg_menu_list.c src/hall.c\
	  src/ssg_debug_text.c src/ssg_gui.c src/ssg.c
OBJ = ${SRC:.c=.o}

all: main

main: ${OBJ}

.PHONY: clean

clean:
	rm -f main ${OBJ}



# END
