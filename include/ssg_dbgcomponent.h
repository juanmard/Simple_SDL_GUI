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

    SSG_bool moving;
    SSG_bool sizing;
    Position offset;

    
    // TODO: Move in another place for ann access from all components.
    SDL_Cursor* nor_cursor;
    SDL_Cursor* mov_cursor;
    SDL_Cursor* siz_cursor;
};

void                init_dbgcomponent   (SSGDbgcomponent* this);
SSGDbgcomponent*    new_dbgcomponent    ();
void                free_dbgcomponent   (SSGDbgcomponent* this);
void                draw_dbgcomponent   (SDL_Renderer* renderer, SSGDbgcomponent* this);
void                update_dbgcomponent (SDL_Event* event, SSGDbgcomponent* this);

#endif
