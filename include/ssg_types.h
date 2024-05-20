#ifndef SSG_TYPES_H
#define SSG_TYPES_H

#include <SDL2/SDL.h>

// TODO: These are basic types. Move to a "ssg.h" file.
typedef struct position {int x, y;} Position;
typedef struct size {int w, h;} Size;
typedef struct color {unsigned int r, g, b, a;} Color;

typedef enum {
    SSG_COMPONENT = 0,
    SSG_DBGCOMPONENT,
    SSG_BASIC,
    SSG_SLIDER,
    SSG_LABEL,
    SSG_BUTTON
} TypeComponent;

typedef enum {
    false = 0,
    true =1
} SSG_bool;


typedef union ssg_component SSGComponent;

// Definition of interface;
typedef void (*ptr_draw)   (SDL_Renderer*, SSGComponent*);
typedef void (*ptr_update) (SDL_Event*, SSGComponent*);
#define PTR_DRAW    void(*)(SDL_Renderer*, SSGComponent*)
#define PTR_UPDATE  void(*)(SDL_Event*, SSGComponent*)

#endif
