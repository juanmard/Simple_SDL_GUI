#ifndef SSG_DBGCOMPONENT_H
#define SSG_DBGCOMPONENT_H

#include <SDL2/SDL.h>
#include "ssg_types.h"

typedef struct ssg_dbgcomponent SSGDbgcomponent;

/*
 */
struct ssg_dbgcomponent
{
    TypeComponent type;
    ptr_update update;
    ptr_draw   draw;    
    Position pos;
    Size     size;
    Color    color;
    void* dad;
    void* son;

    SSG_bool moving;
    SSG_bool sizing;
    Position offset;
};

void                init_dbgcomponent   (SSGDbgcomponent* dbgcomponent);
SSGDbgcomponent*    new_dbgcomponent    ();
void                free_dbgcomponent   (SSGDbgcomponent* dbgcomponent);
void                draw_dbgcomponent   (SDL_Renderer* renderer, SSGDbgcomponent* dbgcomponent);
void                update_dbgcomponent (SDL_Event* event, SSGDbgcomponent* dbgcomponent);

#endif
