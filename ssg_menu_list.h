#ifndef SSG_MENU_LIST_H
#define SSG_MENU_LIST_H

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
