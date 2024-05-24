#ifndef SSG_LABEL_H
#define SSG_LABEL_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
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

    char* text;
    SSG_bool generate;

    TTF_Font* font;
    SDL_Surface* surfaceMessage;
    SDL_Texture* Message;
    SDL_Rect* Message_rect;
};

SSGLabel*  new_label (void);
void       init_label (SSGLabel* this);
void       free_label (SSGLabel* this);

void       draw_label (SDL_Renderer* renderer, SSGLabel* this);
void       update_label (SDL_Event* event, SSGLabel* this);

#endif
