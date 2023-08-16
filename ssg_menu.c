#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "ssg_button.h"
#include "ssg_text.h"
#include "ssg_menu.h"
#include "my_str.h"

//BUTTON LIST

struct ssg_button_list* new_button_list()
{
    /* returns a pointer to a new heap allocated (empty) linked list
       of button pointers
     */
    struct ssg_button_list* new =
        malloc(sizeof(struct ssg_button_list));
    new->button = NULL;
    new->next = NULL;
    return new;
}

void add_button_to_list(struct ssg_button_list* list,
                        struct ssg_button* new)
{
    struct ssg_button_list* p = list;
    while (p->next)
        p = p->next;
    p->next = malloc(sizeof(struct ssg_button_list));
    p->next->button = new;
    p->next->next = NULL;
}

void free_button_list(struct ssg_button_list* list)
{
    struct ssg_button_list* p = list;
    struct ssg_button_list* p2 = list;
    while(p)
    {
        p2 = p->next;
        if(p->button)
            free_button(p->button);
        free(p);
        p = p2;
    }
}

void print_button_list(SDL_Renderer* renderer,
                       struct ssg_button_list* list,
                       SDL_Surface* font)
{
    struct ssg_button_list* p = list->next;
    while(p)
    {
        print_ssg_button(renderer, p->button, font);
        p = p->next;
    }
}

struct ssg_button* is_button_pressed_from_name(
    struct ssg_button_list* list, char* name, int x, int y)
{
    struct ssg_button_list* p = list->next;
    while (p && !are_arrays_equal(p->button->nombre, name))
           p = p->next;
    if ( !p )
        return NULL;
    else
    {
        if (is_ssg_button_pressed(p->button, x, y))
            return p->button;
        else
            return NULL;
    }
}

void print_button_list_console(struct ssg_button_list* list)
{
    struct ssg_button_list* p = list;
    size_t i = 0;
    while (p)
    {
        p = p->next;
        i++;
    }
}

// TEXT LIST

struct ssg_text_list* new_text_list()
{
    /* returns a pointer to a new heap allocated (empty) linked list
       of button pointers
     */
    struct ssg_text_list* new =
        malloc(sizeof(struct ssg_text_list));
    new->text = NULL;
    new->next = NULL;
    return new;
}

void add_text_to_list(struct ssg_text_list* list,
                        struct ssg_text* new)
{
    struct ssg_text_list* p = list;
    while (p->next)
        p = p->next;
    p->next = malloc(sizeof(struct ssg_text_list));
    p->next->text = new;
    p->next->next = NULL;
}

void free_text_list(struct ssg_text_list* list)
{
    struct ssg_text_list* p = list;
    struct ssg_text_list* p2 = list;
    while(p)
    {
        p2 = p->next;
        if(p->text)
            free_text(p->text);
        free(p);
        p = p2;
    }
}

void print_text_list(SDL_Renderer* renderer,
                     struct ssg_text_list* list,
                     SDL_Surface* font)
{
    struct ssg_text_list* p = list->next;
    while(p)
    {
        print_ssg_text(renderer, p->text, font);
        p = p->next;
    }
}

void print_text_list_console(struct ssg_text_list* list)
{
    struct ssg_text_list* p = list;
    size_t i = 0;
    while (p)
    {
        // FALTAN LOS PRINT XD
        p = p->next;
        i++;
    }
}

/*
    MENU
 */

struct ssg_menu* new_menu(char* name)
{
    struct ssg_menu* new = malloc(sizeof(struct ssg_menu));
    strncpy(new->name, name, MENU_NAME_LIMIT);
    *(new->name + MENU_NAME_LIMIT - 1) = 0;
    new->buttons = new_button_list();
    new->texts = new_text_list();
    return new;
}

void add_text_to_menu(struct ssg_menu* menu,
                        struct ssg_text* new)
{
    add_text_to_list(menu->texts, new);
}

void add_button_to_menu(struct ssg_menu* menu,
                        struct ssg_button* new)
{
    add_button_to_list(menu->buttons, new);
}

void free_menu(struct ssg_menu* menu)
{
    free_button_list(menu->buttons);
    free_text_list(menu->texts);
    free(menu);
}

void print_menu(SDL_Renderer* renderer, struct ssg_menu* menu,
                SDL_Surface* font)
{
    print_button_list(renderer, menu->buttons, font);
    print_text_list(renderer, menu->texts, font);
}
