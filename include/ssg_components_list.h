#ifndef SSG_COMPONENTS_LIST_H
#define SSG_COMPONENTS_LIST_H

#include "ssg_component.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/*
An "ssg_components_list" is a linked list where each element has a pointer
to each one of the "ssg_component" that shape the program/GUI (so as a
pointer to the next element of the linked list).
*/
struct ssg_components_list
{
    struct ssg_component* component;
    struct ssg_components_list* next;
};
typedef struct ssg_components_list SSGComponents;

struct ssg_components_list* new_components_list ();
struct ssg_component*       add_component (struct ssg_components_list *list);
void                        free_component_list (struct ssg_components_list *list);

#endif
