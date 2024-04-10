#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "ssg_button.h"
#include "ssg_text.h"
#include "ssg_menu.h"
#include "my_str.h"

//BUTTON LIST

/*
   new_button_list()
   Returns a pointer to a new heap allocated ssg_button_list
 */
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

/*
   add_button_to_list()
   Adds the ssg_button pointed to by new to the ssg_button_list pointed
   to by list. The function searches the last element of the linked
   list, allocates a new ssg_button_list, and sets its fields
 */
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

/*
   free_button_list()
   Frees the memory region pointed to by list, so as every button
   stored in the ssg_button_list linked list
 */
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

/*
   print_button_list()
   Displays all the ssg_buttons stored in the ssg_button_list pointed
   to by list on the SDL_Renderer* renderer, with the font "font"
 */
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

/*
   is_button_pressed_from_name()
   Returns the pointer to the ssg_button the name of which is name,
   stored in the ssg_button_list pointed to by list if it has been
   pressed, when clicking on the coordinates (x,y)
 */
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

/*
** is_text_pressed_from_name
*/
struct ssg_text* is_text_pressed_from_name(
    struct ssg_text_list* list, char* name, int x, int y)
{
    struct ssg_text_list* p = list->next;
    while (p && !are_arrays_equal(p->text->name, name))
           p = p->next;
    if ( !p )
        return NULL;
    else
    {
        if (is_ssg_text_pressed(p->text, x, y))
            return p->text;
        else
            return NULL;
    }
}

/*
   print_button_list_console()
   This function is used for debugging, it prints the ssg_button_list
   pointed to by list on the standard output stream
 */
void print_button_list_console(struct ssg_button_list* list)
{
    struct ssg_button_list* p = list;
    size_t i = 0;
    while (p)
    {
        printf("\
elt number %zu\n\
pointer: %p\n\
button: %p\n\
next: %p\n", i, p, p->button, p->next);
        p = p->next;
        i++;
    }
}

// TEXT LIST

/*
   new_text_list()
   Analog to new_button_list()
   Returns a pointer to a new heap allocated (empty) linked list
   of button pointers
 */
struct ssg_text_list* new_text_list()
{
    struct ssg_text_list* new =
        malloc(sizeof(struct ssg_text_list));
    new->text = NULL;
    new->next = NULL;
    return new;
}

/*
   add_text_to_list()
   Analog to add_button_to_list()
 */
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

/*
   free_text_list()
   Analog to free_button_list()
 */
void free_text_list(struct ssg_text_list* list)
{
    struct ssg_text_list* p = list;
    struct ssg_text_list* p2 = list->next;
    // freeing only the text_list for the sentinel
    // because the text itself will be freed later
    free(p);
    p = p2;
    while(p)
    {
        p2 = p->next;
        if(p->text)
        {
            free_text(p->text);
        }
        free(p);
        p = p2;
    }
}

/*
   print_text_list()
   Analog to print_button_list()
 */
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

/*
   print_text_list_console()
   Analog to print_button_list_console()
 */
void print_text_list_console(struct ssg_text_list* list)
{
    struct ssg_text_list* p = list;
    size_t i = 0;
    while (p)
    {
        printf("\
elt number %zu\n\
pointer: %p\n\
text: %p\n\
next: %p\n", i, p, p->text, p->next);
        p = p->next;
        i++;
    }
}

void set_focused_text(struct ssg_text_list *list, struct ssg_text *text)
{
    list->text = text;
}

int write_to_focused_text_input(struct ssg_text_list *list,
                                SDL_TextInputEvent input)
{
    struct ssg_text *text = list->text;
    if (!text)
    {
        return -1;
    }

    add_letter(text, input.text[0]);
}

int write_to_focused_text(struct ssg_text_list *list, SDL_KeyboardEvent key)
{
    //int c = key.keysym.sym;
    SDL_Scancode s = key.keysym.scancode;
    int c = SDL_GetKeyFromScancode(s);
    int mod = key.keysym.mod;
    struct ssg_text *text = list->text;
    if (!text)
    {
        return -1;
    }
    //printf("%d\n", SDL_GetKeyFromScancode(c));
    //add_letter(text, SDL_GetKeyFromScancode(c));
    if (c >= 'a' && c <= 'z')
    {
        if (mod & KMOD_SHIFT)
        {
            add_letter(text, c - 'a' + 'A');
        }
        else
        {
            add_letter(text, c);
        }
    }
    else if (c >= 32 && c <= 126)
    {
        add_letter(text, c);
    }
    else if (c == 8)
    {
        pop_letter(text);
    }
    return 0;
}

/*
    MENU
 */

/*
   new_menu()
   Returns a pointer to a new heap allocated ssg_menu with the given
   name. It also allocates a new empty ssg_button_list and
   ssg_text_list
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

/*
   add_text_to_menu()
   Adds the ssg_text pointed to by new to the ssg_menu pointed to by
   menu. It only calls the add_text_to_list() function. The purpose
   of this function is to be able to add elements to menus easier
 */
void add_text_to_menu(struct ssg_menu* menu,
                        struct ssg_text* new)
{
    add_text_to_list(menu->texts, new);
}

/*
   add_button_to_menu()
   Analog to add_text_to_menu()
 */
void add_button_to_menu(struct ssg_menu* menu,
                        struct ssg_button* new)
{
    add_button_to_list(menu->buttons, new);
}

/*
   free_menu()
   Frees the memory region pointed to by menu, so as the
   ssg_button_list and ssg_text_list pointed to by menu's buttons and
   texts fields
 */
void free_menu(struct ssg_menu* menu)
{
    free_button_list(menu->buttons);
    free_text_list(menu->texts);
    free(menu);
}

/*
   print_menu()
   Displays all the ssg_buttons in the ssg_button_list poitned to by
   menu->buttons and all the ssg_texts in the ssg_text_list pointed
   to by menu->texts by calling print_button_list() and
   print_text_list()
 */
void print_menu(SDL_Renderer* renderer, struct ssg_menu* menu,
                SDL_Surface* font)
{
    print_button_list(renderer, menu->buttons, font);
    print_text_list(renderer, menu->texts, font);
}
