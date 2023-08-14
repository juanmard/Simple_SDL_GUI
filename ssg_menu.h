#ifndef SSG_MENU_H
#define SSG_MENU_H

struct ssg_button_list
{
    struct ssg_button* button;
    struct ssg_button_list* next;
};

struct ssg_button_list* new_button_list();
void add_button_to_list(struct ssg_button_list* list,
                        struct ssg_button* new);
void free_button_list(struct ssg_button_list* list);
void print_button_list(SDL_Renderer* renderer,
                       struct ssg_button_list* list);
struct ssg_button* is_button_pressed_from_name(struct ssg_button_list* list,
                                char* name, int x, int y);
void print_button_list_console(struct ssg_button_list* list);

#endif
