#ifndef SSG_GUI_H
#define SSG_GUI_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "ssg_menu_list.h"

struct ssg_gui
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Surface *font;
    struct ssg_menu_list *menu_list;
};

struct ssg_gui *init_gui(char *window_name);
int set_font(struct ssg_gui *gui, char *filename);
void close_gui(struct ssg_gui *gui);

#endif /* ! SSG_GUI_H */
