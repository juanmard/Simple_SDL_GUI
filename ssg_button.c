#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>

#include "ssg_button.h"
#include "ssg_text.h"


int is_ssg_button_pressed(struct ssg_button* button, int x, int y)
{
    return x>=button->x && x<=button->x+button->w
        && y>=button->y && y<=button->y+button->h;
}

void print_ssg_button(SDL_Renderer* renderer,
                      struct ssg_button* button)
{
    SDL_Color rgb;
    SDL_GetRenderDrawColor(renderer, &rgb.r, &rgb.g, &rgb.b, &rgb.a);
    SDL_SetRenderDrawColor(renderer, button->red2, button->green2,
                           button->blue2, 0xFF);
    SDL_RenderDrawLine(renderer, button->x, button->y,
                       button->x+button->w, button->y);
    SDL_RenderDrawLine(renderer, button->x, button->y+button->h,
                       button->x+button->w, button->y+button->h);
    SDL_RenderDrawLine(renderer, button->x, button->y,
                       button->x, button->y+button->h);
    SDL_RenderDrawLine(renderer, button->x+button->w, button->y,
                       button->x+button->w, button->y+button->h);

    // filling the rectangle with the primary colour
    SDL_SetRenderDrawColor(renderer, button->visible_red,
                           button->visible_green,
                           button->visible_blue, 0xFF);
    for (int i = 0; i < button->h-1; i++)
        SDL_RenderDrawLine(renderer, button->x+1, button->y+1+i,
                           button->x+button->w-1, button->y+1+i);
    SDL_SetRenderDrawColor(renderer, rgb.r, rgb.g, rgb.b, rgb.a);

    // writing the tag of the button
    print_ssg_text(renderer, button->tag);
}

void * button_press_feedback(void* button_v)
{
    struct ssg_button* button = (struct ssg_button*)button_v;

    if(button->red>191)
        button->visible_red = 255;
    else
        button->visible_red = button->red + 64;

    if(button->green>191)
        button->visible_green = 255;
    else
        button->visible_green = button->green + 64;

    if(button->blue>191)
        button->visible_blue = 255;
    else
        button->visible_blue = button->blue + 64;

    struct timespec tme = { 0, 5000000};

    for (size_t i = 0; i<64; i++)
    {
        if(button->visible_red > button->red)
            button->visible_red -= 1;
        if(button->visible_green > button->green)
            button->visible_green -= 1;
        if(button->visible_blue > button->blue)
            button->visible_blue -= 1;
        nanosleep(&tme, NULL);
     }

    return NULL;
}

void clrcpy(struct ssg_button* button)
{
    button->visible_red = button->red;
    button->visible_green = button->green;
    button->visible_blue = button->blue;
}

void free_button(struct ssg_button* button)
{
    free_text(button->tag);
    free(button);
}

struct ssg_button* new_button_std(int x, int y, char nombre[],
                       int red, int green, int blue, char* tag)
{
    /* this is a fast way to create a button under the SSG standard
     */
    struct ssg_button* new_button = malloc(sizeof(struct ssg_button));
    new_button->x = x;
    new_button->y = y;
    new_button->w = 80;
    new_button->h = 50;
    strncpy(new_button->nombre, nombre, BUTTON_NAME_LIMIT);
    new_button->nombre[BUTTON_NAME_LIMIT - 1] = 0;

    new_button->red = red;
    new_button->green = green;
    new_button->blue = blue;

    clrcpy(new_button);

    /* chosing the button's border color: white if the button's color
       is dark, dark grey otherwise
     */
    int average_color = (red + green + blue) / 3;

    if (average_color < 128)
    {
        new_button->red2 = 0xFF;
        new_button->green2 = 0xFF;
        new_button->blue2 = 0xFF;
    }
    else
    {
        new_button->red2 = 0x44;
        new_button->green2 = 0x44;
        new_button->blue2 = 0x44;
    }

    new_button->tag = new_ssg_text(x+2, y+2, 80-4, 50-4,
                                   new_button->red2,
                                   new_button->green2,
                                   new_button->blue2, tag);
    return new_button;
}
