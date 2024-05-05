#include "ssg_basic.h"

/*
TODO: 
*/
void draw_basic (SDL_Renderer* renderer, SSGBasic* basic){
    SDL_SetRenderDrawColor (renderer,
                    basic->color.r,
                    basic->color.g,
                    basic->color.b,
                    basic->color.a);
    SDL_Rect bounds;
    bounds.x = basic->pos.x;
    bounds.y = basic->pos.y;
    bounds.w = basic->size.w;
    bounds.h = basic->size.h;
    SDL_RenderDrawRect (renderer, &bounds);
};


/*
TODO: 
*/
void draw_basic_test (SDL_Renderer* renderer, SSGBasic* basic){
    SDL_SetRenderDrawColor (renderer,
                            basic->color.r,
                            basic->color.g,
                            basic->color.b,
                            basic->color.a);
    SDL_Rect bounds;
    bounds.x = basic->pos.x;
    bounds.y = basic->pos.y;
    bounds.w = basic->size.w;
    bounds.h = basic->size.h;
    SDL_RenderDrawLine (renderer, bounds.x, bounds.y, bounds.x+bounds.w, bounds.y+bounds.h);
    SDL_RenderDrawLine (renderer, bounds.x+bounds.w, bounds.y, bounds.x, bounds.y+bounds.h);
};

/*
TODO: 
*/
void update_basic (SDL_Event* event, SSGBasic* basic){

    // Mouse click coords from event handler.
    SDL_Point mousePosition;
    mousePosition.x = event->motion.x; 
    mousePosition.y = event->motion.y;

    // Limits from basic component.
    SDL_Rect limits;
    limits.x = basic->pos.x;
    limits.y = basic->pos.y;
    limits.w = basic->size.w;
    limits.h = basic->size.h;

    if (SDL_PointInRect(&mousePosition, &limits)) {
        switch(event->type)
        {
            case SDL_MOUSEBUTTONDOWN:
                if (event->button.button == SDL_BUTTON_RIGHT) {
                    basic->draw = &draw_basic_test;
                } else {
                    basic->draw = &draw_basic;
                }
                basic->color.r = 0xFF;
                basic->color.g = 0x00;
                break;
            
            case SDL_MOUSEBUTTONUP:
                basic->color.r = 0x00;
                basic->color.g = 0xFF;
                break;
            
            default:
                break;
        }
    }
};

/*
   new_basic()
*/
SSGBasic* new_basic (SSGComponent* component) {
    SSGBasic* new = malloc(sizeof(SSGBasic));
    new->dad = component;
    new->son = NULL;
    return new;
}

/*
    init_basic ()
    For a basic initialization test.
*/
void init_basic  (SSGBasic* basic){
    basic->type = SSG_BASIC;
    // basic->dad = ...;
    // basic->son = NULL;
    basic->update = &update_basic;
    basic->draw = &draw_basic;

    basic->pos = (Position){250, 260};
    basic->size = (Size){100, 15};
    basic->color = (Color){0x00, 0xFF, 0x00, 0xFF};
};

/*
TODO: 
*/
void free_basic (SSGBasic* basic){
    if (basic->son == NULL) {
        // Break the link with his father and then...
        basic->dad->son = NULL;
        // ...be free.
        free (basic);
    }
    // TODO: ...else {free first his own son}.
};
