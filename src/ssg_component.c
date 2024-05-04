#include "ssg_component.h"
#include "ssg_slider.h"

void draw_component (SDL_Renderer* renderer, SSGComponent* component){
    switch (component->type)
    {
        case SSG_BASIC:
            SDL_SetRenderDrawColor (renderer,
                            component->color.r,
                            component->color.g,
                            component->color.b,
                            component->color.a);
            SDL_Rect bounds;
            bounds.x = component->pos.x;
            bounds.y = component->pos.y;
            bounds.w = component->size.w;
            bounds.h = component->size.h;
            SDL_RenderDrawRect (renderer, &bounds);
            break;
        
        case SSG_SLIDER:
            draw_slider (renderer, (SSGSlider*) component->son);
            break;

        case SSG_BUTTON:
        default:
            break;
    }
};


void draw_component_test (SDL_Renderer* renderer, SSGComponent* component){
    SDL_SetRenderDrawColor (renderer,
                            component->color.r,
                            component->color.g,
                            component->color.b,
                            component->color.a);
    SDL_Rect bounds;
    bounds.x = component->pos.x;
    bounds.y = component->pos.y;
    bounds.w = component->size.w;
    bounds.h = component->size.h;
    SDL_RenderDrawLine (renderer, bounds.x, bounds.y, bounds.x+bounds.w, bounds.y+bounds.h);
    SDL_RenderDrawLine (renderer, bounds.x+bounds.w, bounds.y, bounds.x, bounds.y+bounds.h);
};

void update_component (SDL_Event*  event, SSGComponent* component){

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
          case SDL_MOUSEBUTTONDOWN:
            if (event->button.button == SDL_BUTTON_RIGHT) {
                component->draw = &draw_component_test;
            } else {
                component->draw = &draw_component;
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
    component->draw = &draw_component;
    component->update = &update_component;
    component->type = SSG_BASIC;
    component->son = NULL;
};

/*
   new_component()
*/
SSGComponent* new_component () {
    SSGComponent* new = malloc(sizeof(SSGComponent));
    return new;
}

void free_component (SSGComponent* component){};
