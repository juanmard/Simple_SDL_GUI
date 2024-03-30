#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "graphic_utils.h"
#include "ssg_text.h"
#include "ssg_menu.h"
#include "ssg_menu_list.h"
#include "ssg_debug_text.h"

/*
   print_ssg_debug_text()
   Analog to print_ssg_text(), but works with ssg_debug_text
   To be precise, it also draws a black rectangle behind the text
   AND it updates the text field of the ssg_debug_text pointed to by
   text depending on the type of variable pointed to by the
   value_type field BEFORE displaying it
 */
void print_ssg_debug_text(SDL_Renderer* renderer,
                    struct ssg_debug_text* text,
                    SDL_Surface* font)
{
    /*
        TODO: optimize the drawing of the black rectangle
     */

    switch(text->value_type)
    {
    case integer: ; // emtpy statement
        int* i_pointer = (int*) text->value;
        snprintf(text->text, SSG_TEXT_LIMIT, "%d", *i_pointer);
        break;
    case pointer: ;
        char* the_pointer= *(char**)text->value;
        snprintf(text->text, SSG_TEXT_LIMIT, "%p", the_pointer);
        break;
    case str: ; // emtpy statement
        char* c_pointer = (char*) text->value;
        snprintf(text->text, SSG_TEXT_LIMIT, "%s", c_pointer);
        break;
    }
    *( text->text + SSG_TEXT_LIMIT - 1 ) = 0;

    SDL_Color clr;
    clr.r = text->red;
    clr.g = text->green;
    clr.b = text->blue;
    clr.a = 0xFF;

    SDL_Color render_color;
    SDL_GetRenderDrawColor(renderer, &render_color.r, &render_color.g,
                           &render_color.b, &render_color.a);

    int letters_per_row = text->w/7;
    int letters_per_col = text->h/10;

    char* curr_let = text->text;


    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    /*
    for (int i = 0; i < text->h-1; i++)
    {
        SDL_RenderDrawLine(renderer, text->x+1, text->y+1+i,
                           text->x+text->w-1, text->y+1+i);
    }
    */

    // printing all the black rectangles (before the letters)

    for (int j = 0; j<letters_per_col; j++)
    {
        if (!*curr_let)
            break;
        for (int i = 0; i<letters_per_row; i++)
        {
            if (!*curr_let)
                break;

            for (int k = 0; k<10; k++)
            {
                SDL_RenderDrawLine(renderer, text->x+(i*7),
                                   text->y+(j*10)+k,
                                   text->x+(i*7)+7, text->y+(j*10)+k);
            }
            curr_let++;
        }
    }
    curr_let = text->text;

    SDL_SetRenderDrawColor(renderer, clr.r, clr.g, clr.b, clr.a);

    for (int j = 0; j<letters_per_col; j++)
    {
        if (!*curr_let)
            break;
        for (int i = 0; i<letters_per_row; i++)
        {
            if (!*curr_let)
                break;
            if (*curr_let == ' ')
            {
                curr_let++;
                continue;
            }
            print_letter(renderer, curr_let, text->x+(i*7),
                         text->y+(j*10), font);
            curr_let++;
        }
    }
    SDL_SetRenderDrawColor(renderer, render_color.r, render_color.g,
                           render_color.b, render_color.a);
}

/*
   free_debug_text()
   Analog to free_text()
 */
void free_debug_text(struct ssg_debug_text* text)
{
    /* frees the memory in which the ssg_debug_text is allocated
     */
    free(text->text);
    free(text);
}

/*
   new_ssg_debug_text()
   Analog to new_ssg_text()
 */
struct ssg_debug_text* new_ssg_debug_text(int x, int y, int w, int h,
                                          int red, int green, int blue,
                                          enum value_type value_type,
                                          void* value)
{
    struct ssg_debug_text* new_text = malloc(sizeof(struct ssg_debug_text));
    new_text->text = malloc(sizeof(char) * SSG_TEXT_LIMIT);
    new_text->x = x;
    new_text->y = y;
    new_text->w = w;
    new_text->h = h;
    new_text->red = red;
    new_text->green = green;
    new_text->blue = blue;
    new_text->value_type = value_type;
    new_text->value = value;

    return new_text;
}

/*
   The sole purpose of this function is to serve the kind of
   ssg_debug_texts that display the name of the current menu
   in the screen. It updates the value field, which points to
   the variable that must be displayed, it sets it to the name
   of the menu that is currently being displayed, which is also
   the menu field of the first element of the ssg_menu_list
   (the sentinel)
 */
void update_menu_name_pointer(struct ssg_debug_text* text,
                              struct ssg_menu_list* menu_list)
{
    text->value = menu_list->menu->name;
}
