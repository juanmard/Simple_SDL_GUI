/*
TODO: Description.
*/
#include <SDL2/SDL.h>

#include "ssg_label.h"
#include "ssg_basic.h"

SSGLabel* new_label () {
    SSGLabel* label = malloc (sizeof(SSGLabel));
    init_label  (label);
    return label;
};

void init_label (SSGLabel* label){
    label->type = SSG_LABEL;
    label->pos = (Position) {10,100};
    label->size = (Size) {200,30};
    label->color = (Color) {0xFF, 0x00, 0x00, 0xFF};

    // Init draw function.
//    label->draw = (PTR_DRAW) &draw_label;
//    label->update = (PTR_UPDATE) &update_label;
    label->draw = (PTR_DRAW) &draw_basic;
    label->update = (PTR_UPDATE) &update_basic;
};

/*
TODO: Description and implementation.
*/
void free_label (SSGLabel* label){
    free (label);
};

/*
TODO: Description.
*/
void draw_label (SDL_Renderer* renderer, SSGLabel* label){
    SDL_RenderDrawRectF (renderer, \
                &(SDL_Rect){label->pos.x, \
                            label->pos.y, \
                            label->size.w, \
                            label->size.h});
};

/*
TODO: Description.
*/
void update_label (SDL_Event* event, SSGLabel* label){
};
