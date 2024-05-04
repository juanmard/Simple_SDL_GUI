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


void draw_component_test (SDL_Renderer *renderer, SSGComponent *component){
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
    SDL_RenderDrawLine (renderer, marco.x, marco.y, marco.x+marco.w, marco.y+marco.h);
    SDL_RenderDrawLine (renderer, marco.x+marco.w, marco.y, marco.x, marco.y+marco.h);
};

void update_component (SDL_Event *event, SSGComponent *component){

    // Mouse click coords from event handler.
    SDL_Point mousePosition;
    mousePosition.x = event->motion.x; 
    mousePosition.y = event->motion.y;

    // Limits from component.
    SDL_Rect limits;
    limits.x = component->pos.x;
    limits.y = component->pos.y;
    limits.w = component->size.w;
    limits.h = component->size.h;

    if (SDL_PointInRect(&mousePosition, &limits)) {
       switch(event->type)
        {
//        case SDL_TEXTEDITING:
//        case SDL_TEXTINPUT:
//        case SDL_KEYUP:
//        case SDL_KEYDOWN:
//        case SDL_QUIT:
//        case SDL_WINDOWEVENT:
//        case SDL_MOUSEMOTION:
          case SDL_MOUSEBUTTONDOWN:
            if (event->button.button == SDL_BUTTON_RIGHT) {
                component->draw = (void*) &draw_component_test;
            } else {
                component->draw = (void*) &draw_component;
            }
            component->color.r = 0xFF;
            component->color.g = 0x00;
            break;
          case SDL_MOUSEBUTTONUP:
            component->color.r = 0x00;
            component->color.g = 0xFF;
            break;
        }
    }
};


/*
    init_component ()
    For a basic initialization test.
*/
void init_component  (SSGComponent* component){
    component->pos = (Position){250, 260};
    component->size = (Size){100, 15};
    component->color = (Color){0x00, 0xFF, 0x00, 0xFF};
    component->draw = (void*) &draw_component;
    component->update = (void*) &update_component;
};

/*
   new_component()
*/
SSGComponent* new_component () {
    SSGComponent* new = malloc(sizeof(SSGComponent));
    return new;
}

void free_component (SSGComponent* component){};
