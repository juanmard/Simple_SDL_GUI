#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "my_str.h"
#include "ssg_menu.h"
#include "ssg_menu_list.h"

#include "welcome.h"
#include "hall.h"

struct ssg_menu_list* new_menu_list()
{
    struct ssg_menu_list* new = malloc(sizeof(struct ssg_menu_list));
    new->menu = NULL;
    new->next = NULL;
    return new;
}

struct ssg_menu* add_menu(struct ssg_menu_list* list, char* name)
{
    struct ssg_menu_list* p = list;
    while (p->next)
        p = p->next;
    p->next = malloc(sizeof(struct ssg_menu_list));
    p->next->menu = new_menu(name);
    p->next->next = NULL;
    return p->next->menu;
}

void free_menu_list(struct ssg_menu_list* list)
{
    struct ssg_menu_list* p = list;
    struct ssg_menu_list* p2 = list->next;

    /* special case: the sentinel
       menu_lists' sentinels have a non NULL value in menu field
       we must not free it, since it will be freed later
     */
    free(p);
    p = p2;
    while(p)
    {
        p2 = p->next;
        free_menu(p->menu);
        free(p);
        p = p2;
    }
}

struct ssg_menu* find_menu_name(struct ssg_menu_list* list,
                                char* name)
{
    struct ssg_menu_list* p = list->next;
    while (p && !are_arrays_equal(p->menu->name, name))
        p = p->next;
    if ( !p )
        return NULL;
    else
        return p->menu;
}

int enable_menu(struct ssg_menu_list* list, struct ssg_menu* menu)
{
    if (menu == NULL)
        return 1;
    else
    {
        list->menu = menu;
        return 0;
    }
}

void print_menu_list_console(struct ssg_menu_list* list)
{
    printf("########PRINTING MENU########\n");
    struct ssg_menu_list* p = list;
    size_t i = 0;
    while (p)
    {
        printf("elt no %zu:\npointer: %p\nmenu: %p\nnext: %p\n",
               i, p, p->menu, p->next);
        p = p->next;
        i++;
    }
}

void check_button(struct ssg_menu_list* menu_list,
                  struct ssg_menu* menu, int x, int y,
    SDL_Renderer* renderer)
{
    char name[MENU_NAME_LIMIT];
    strncpy(name, menu->name, MENU_NAME_LIMIT);
    name[MENU_NAME_LIMIT - 1] = 0;
    if (are_arrays_equal(name, "first menu :)"))
        check_pressed_buttons1(menu_list, menu->buttons, x, y,
                               renderer);
    else if (are_arrays_equal(name, "(: second menu"))
        check_pressed_buttons2(menu_list, menu->buttons, x, y,
                               renderer);
}
