#ifndef SSG_MENU_LIST_H
#define SSG_MENU_LIST_H

/*
   An ssg_menu_list is a linked list where each element has a pointer
   to each one of the ssg_menus that shape the program/GUI (so as a
   pointer to the next element of the linked list)
   As all of the other linked list, ssg_menu_list has a sentinel, but
   unlike the other ones, the value of the sentinel in an ssg_menu_list
   is relevant, as the menu field points to the ssg_menu that must be
   displayed at an instant t
 */
struct ssg_menu_list
{
    struct ssg_menu* menu;
    struct ssg_menu_list* next;
};

struct ssg_menu_list* new_menu_list();
struct ssg_menu* add_menu(struct ssg_menu_list* list, char* name);
void free_menu_list(struct ssg_menu_list* list);
struct ssg_menu* find_menu_name(struct ssg_menu_list* list,
                                char* name);
int enable_menu(struct ssg_menu_list* list, struct ssg_menu* menu);
void print_menu_list_console(struct ssg_menu_list* list);
void check_button(struct ssg_menu_list* menu_list,
                  struct ssg_menu* menu, int x, int y,
                  SDL_Renderer* renderer);

#endif
