/*
TODO: Description.
*/
#include <SDL2/SDL.h>

#include "ssg_label.h"

SSGLabel* new_label () {
    SSGLabel* label = malloc (sizeof(SSGLabel));
    init_label  (label);
    return label;
};

void init_label (SSGLabel* label){
    label->type = SSG_LABEL;
    label->pos = (Position) {250,320};
    label->size = (Size) {200,30};
    label->color = (Color) {0x00, 0x00, 0xFF ,0xFF};

    // Init draw function.
    label->draw = (PTR_DRAW) &draw_label;
    label->update = (PTR_UPDATE) &update_label;
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
};

/*
TODO: Description.
*/
void update_label (SDL_Event* event, SSGLabel* label){
};
