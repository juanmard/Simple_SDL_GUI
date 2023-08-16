#ifndef SSG_BUTTON_H
#define SSG_BUTTON_H

#define BUTTON_NAME_LIMIT 30
#define BUTTON_TAG_LIMIT 15

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
};

int is_ssg_button_pressed(struct ssg_button* button, int x, int y);

void print_ssg_button(SDL_Renderer* renderer, struct ssg_button* button,
                      SDL_Surface* font);

void * button_press_feedback(void* button_v);

void clrcpy(struct ssg_button* button);

void free_button(struct ssg_button* button);

struct ssg_button* new_button_std(int x, int y, char nombre[],
                       int red, int green, int blue, char* tag);

#endif
