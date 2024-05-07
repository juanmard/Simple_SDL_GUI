#ifndef SSG_COMPONENTS_LIST_H
#define SSG_COMPONENTS_LIST_H

#include <SDL2/SDL.h>
#include "ssg_component.h"

/*
An "ssg_components_list" is a linked list where each element has a pointer
to each one of the "ssg_component" that shape the program/GUI (so as a
pointer to the next element of the linked list).
*/
typedef struct ssg_components_list SSGComponents;
struct ssg_components_list
{
    SSGComponent*  component;
    SSGComponents* next;
};

SSGComponents*  new_components_list ();
void            add_component (SSGComponents* list, SSGComponent* component);
void            free_components_list (SSGComponents* list);

#endif
