#ifndef SSG_MENU_H
#define SSG_MENU_H

#define MENU_NAME_LIMIT 15
struct ssg_button_list
{
    struct ssg_button* button;
    struct ssg_button_list* next;
};

struct ssg_text_list
{
    struct ssg_text* text;
    struct ssg_text_list* next;
};

struct ssg_menu
{
    char name[MENU_NAME_LIMIT];
    struct ssg_button_list* buttons;
    struct ssg_text_list* texts;
};

// BUTTON LIST

struct ssg_button_list* new_button_list();
void add_button_to_list(struct ssg_button_list* list,
                        struct ssg_button* new);
void free_button_list(struct ssg_button_list* list);
void print_button_list(SDL_Renderer* renderer,
                       struct ssg_button_list* list,
                       SDL_Surface* font);
struct ssg_button* is_button_pressed_from_name(struct ssg_button_list* list,
                                char* name, int x, int y);
void print_button_list_console(struct ssg_button_list* list);

// TEXT LIST

struct ssg_text_list* new_text_list();
void add_text_to_list(struct ssg_text_list* list,
                        struct ssg_text* new);
void free_text_list(struct ssg_text_list* list);
void print_text_list(SDL_Renderer* renderer,
                     struct ssg_text_list* list,
                     SDL_Surface* font);
void print_text_list_console(struct ssg_text_list* list);

// MENU
struct ssg_menu* new_menu(char* name);
void add_text_to_menu(struct ssg_menu* menu,
                        struct ssg_text* new);
void add_button_to_menu(struct ssg_menu* menu,
                        struct ssg_button* new);
void free_menu(struct ssg_menu* menu);
void print_menu(SDL_Renderer* renderer, struct ssg_menu* menu,
                SDL_Surface* font);

#endif
