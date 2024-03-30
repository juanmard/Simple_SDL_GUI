#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "my_str.h"
#include "ssg_menu.h"
#include "ssg_menu_list.h"

#include "welcome.h"
#include "hall.h"

/*
   new_menu_list()
   Returns a pointer to a new heap allocated ssg_menu_list
 */
struct ssg_menu_list* new_menu_list()
{
    struct ssg_menu_list* new = malloc(sizeof(struct ssg_menu_list));
    new->menu = NULL;
    new->next = NULL;
    return new;
}

/*
   add_menu()
   Adds a new heap allocated ssg_menu with a given name to the
   ssg_menu_list pointed to by list. Allocates a new ssg_menu_list too,
   which is a new element in the linked list
 */
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

/*
   free_menu_list()
   Frees the memory region pointed to by list, so as each menu in the
   ssg_menu_list and each ssg_button_list and each ssg_text_list in
   each of those ssg_menus
 */
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

/*
   find_menu_name()
   Returns the pointer to an ssg_menu the name of which is name, as
   long as it is stored in the ssg_menu_list pointed to by list
 */
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

/*
   enable_menu()
   Makes list->menu point to the ssg_menu pointed to by menu, where
   list is a pointer to an ssg_menu_list. In other words, it
   activates an ssg_menu, which means changing the current ssg_menu
   that is being displayed
 */
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

/*
   print_menu_list_console()
   For debugging purposes only
   Prints the ssg_menu_list pointed to by list on the standard
   output stream
 */
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

/*
   check_button()
   Calls the proper function to handle which ssg_button is being
   pressed depending on the current ssg_menu. menu_list points to the
   ssg_menu_list that stores all of the ssg_menus. menu points to the
   current menu, which is also the menu field of the sentinel of the
   ssg_menu_list linked list. (x,y) are the coordinates where the
   Mouse Left Button has been pressed. renderer points to the
   SDL_Renderer where the buttons are being displayed
 */
int check_button(struct ssg_menu_list* menu_list,
                  struct ssg_menu* menu, int x, int y,
                  SDL_Renderer* renderer)
{
    char name[MENU_NAME_LIMIT];
    strncpy(name, menu->name, MENU_NAME_LIMIT);
    name[MENU_NAME_LIMIT - 1] = 0;
    if (are_arrays_equal(name, "Welcome!"))
        return check_pressed_buttons1(menu_list, menu->buttons, x, y,
                               renderer);
    else if (are_arrays_equal(name, "The Hall"))
        return check_pressed_buttons2(menu_list, menu->buttons, x, y,
                               renderer);
}
