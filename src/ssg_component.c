#include "ssg_component.h"

void draw_component (SDL_Renderer *renderer, SSGComponent *component){
    SDL_SetRenderDrawColor (renderer,
                            component->color.r,
                            component->color.g,
                            component->color.b,
                            component->color.a);
    SDL_Rect marco;
    marco.x = component->pos.x;
    marco.y = component->pos.y;
    marco.w = component->size.w;
    marco.h = component->size.h;
    SDL_RenderDrawRect (renderer, &marco);
};

SSGComponent*  init_component  (SSGComponent* component){
    component->pos = (Position){250, 260};
    component->size = (Size){100, 15};
    component->color = (Color){0x00, 0xFF, 0x00, 0xFF};
    component->draw = &draw_component;
    component->update = NULL;
};

/*
   new_component()
*/
SSGComponent* new_component () {
    SSGComponent* new = malloc(sizeof(SSGComponent));
    return new;
}



void free_component (SSGComponent* component){};
