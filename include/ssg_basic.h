#ifndef SSG_BASIC_H
#define SSG_BASIC_H

#include <SDL2/SDL.h>
#include "ssg_component.h"

typedef struct ssg_basic SSGBasic;

/*
 */
struct ssg_basic
{
    TypeComponent type;
    void* dad;
    void* son;
    ptr_update update;
    ptr_draw   draw;
    
    Position pos;
    Size     size;
    Color    color;
};

void           init_basic   (SSGBasic* basic);
SSGBasic*      new_basic    ();
void           free_basic   (SSGBasic* basic);
void           draw_basic   (SDL_Renderer* renderer, SSGBasic* basic);
void           update_basic (SDL_Event* event, SSGBasic* basic);

#endif
