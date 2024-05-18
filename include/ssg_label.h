#ifndef SSG_LABEL_H
#define SSG_LABEL_H

#include <SDL2/SDL.h>
#include "ssg_types.h"

typedef struct ssg_label SSGLabel;

/*
TODO: Description
 */
struct ssg_label
{
    TypeComponent type;
    ptr_update update;
    ptr_draw   draw;
    Position   pos;
    Size       size;
    Color      color;
    void*      dad;
    void*      son;

};

SSGLabel*  new_label (void);
void       init_label (SSGLabel* label);
void       free_label (SSGLabel* label);

void       draw_label (SDL_Renderer* renderer, SSGLabel* label);
void       update_label (SDL_Event* event, SSGLabel* label);

#endif
