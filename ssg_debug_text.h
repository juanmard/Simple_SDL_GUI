#ifndef SSG_DEBUG_TEXT_H
#define SSG_DEBUG_TEXT_H

/*
   An ssg_debug_text is an object (not OOP) analog to ssg_text, but
   ssg_debug_text is displayed at last before presenting the renderer,
   it is displayed on a black rectangle and it displays the value of
   a variable instead of a fixed string
 */

/*
   This enumeration will help us handle the different types of
   variables that ssg_debug_texts will be able to display
 */
enum value_type
{
    integer,
    pointer,
    str,
};

/*
   The value_type field is the type of variable of the value that
   must be displayed. The value field is a pointer to the value that
   must be displayed. The text field is a string that will
   constantly be updated to represent the value of the variable
   at any moment
 */
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
