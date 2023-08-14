#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "ssg_button.h"
#include "ssg_menu.h"
#include "my_str.h"

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
                       struct ssg_button_list* list)
{
    struct ssg_button_list* p = list->next;
    while(p)
    {
        print_ssg_button(renderer, p->button);
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
