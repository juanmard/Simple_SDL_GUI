#ifndef SSG_DEBUG_TEXT_H
#define SSG_DEBUG_TEXT_H

enum value_type
{
    integer,
    pointer,
    str,
};

struct ssg_debug_text
{
    int size;
    int x;
    int y;
    int w;
    int h;
    int red;
    int green;
    int blue;
    enum value_type value_type;
    void* value;
    char* text;
};
/*
void print_letter(SDL_Renderer* renderer, char* letter, int x, int y,
                  SDL_Surface* font);
*/
void print_ssg_debug_text(SDL_Renderer* renderer,
                          struct ssg_debug_text* text,
                          SDL_Surface* font);
void free_debug_text(struct ssg_debug_text* text);
struct ssg_debug_text* new_ssg_debug_text(int x, int y, int w, int h,
                                          int red, int green, int blue,
                                          enum value_type value_type,
                                          void* value);
void update_menu_name_pointer(struct ssg_debug_text* text,
                              struct ssg_menu_list* menu_list);

#endif
