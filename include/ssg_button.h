#ifndef SSG_BUTTON_H
#define SSG_BUTTON_H

#define BUTTON_NAME_LIMIT 30
#define BUTTON_TAG_LIMIT 15

#include "ssg_gui.h"

/*
   An ssg_button is an object (not the programming meaning, since C
   isn't object oriented) which triggers a piece of code when being
   clicked on. It has a position (x,y), a width w, a height h, a name
   nombre (it's in spanish, I have to change that), a "natural colour"
   encoded by three integers (red, green, blue), the colour of its
   edges (red2, green2, blue2), a the colour that is visible, the
   one that is displayed at a specific moment (visible_red, ...) and
   a ssg_text which is a text displayed on the button (tag)
 */
struct ssg_button
{
    int x;
    int y;
    int w;
    int h;
    char nombre[BUTTON_NAME_LIMIT];

    // this is the button's natural color
    int red;
    int green;
    int blue;

    // this is the colour the button will be showing
    int visible_red;
    int visible_green;
    int visible_blue;

    // this is the button's border colour
    int red2;
    int green2;
    int blue2;

    struct ssg_text* tag;

    SDL_Texture* image;
    SDL_Surface *image_surface;
};

int is_ssg_button_pressed(struct ssg_button* button, int x, int y);

void print_ssg_button(SDL_Renderer* renderer, struct ssg_button* button,
                      SDL_Surface* font);

void * button_press_feedback(void* button_v);

void clrcpy(struct ssg_button* button);

void free_button(struct ssg_button* button);

struct ssg_button* new_button_std(int x, int y, char nombre[],
                       int red, int green, int blue, char* tag);
struct ssg_button* new_button_with_image(int x, int y,
                                         char name[], int red2,
                                         int green2, int blue2,
                                         char* tag,
                                         char *image_path,
                                         struct ssg_gui *gui);

#endif
