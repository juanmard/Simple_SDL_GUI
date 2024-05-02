#ifndef SSG_COMPONENT_H
#define SSG_COMPONENT_H

#include <SDL2/SDL.h>

// TODO: These are basic types. Move to a "ssg.h" file.
typedef struct position {int x, y;} Position;
typedef struct size {int w, h;} Size;
typedef struct color {unsigned int r, g, b, a;} Color;

//TODO: Change in code all structs definitions for typedef.
typedef struct ssg_component SSGComponent;

// Definition of interface;
typedef void (*ptr_draw)   (SDL_Renderer *, SSGComponent *);
typedef void (*ptr_update) (void);

/*
   A "ssg_component" is a basic object which has a position (x,y),
   a size (width, height), a color (red, green, blue, alpha), and
   a reference from how it display (draw) and change (update).
 */
struct ssg_component
{
    Position pos;
    Size     size;
    Color     color;

    ptr_draw   draw;
    ptr_update update;
};

SSGComponent*  init_component  (SSGComponent* component);
SSGComponent*  new_component   (void);
void           free_component  (SSGComponent* component);
void           draw_component  (SDL_Renderer *renderer, SSGComponent *component);

#endif
