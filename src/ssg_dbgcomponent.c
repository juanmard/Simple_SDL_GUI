/*
TODO: 
*/
#include "ssg_dbgcomponent.h"

/*
TODO: 
*/
void draw_dbgcomponent (SDL_Renderer* renderer, SSGDbgcomponent* dbgcomponent){
    SDL_SetRenderDrawColor (renderer,
                    dbgcomponent->color.r,
                    dbgcomponent->color.g,
                    dbgcomponent->color.b,
                    dbgcomponent->color.a);
    SDL_Rect bounds;
    bounds.x = dbgcomponent->pos.x;
    bounds.y = dbgcomponent->pos.y;
    bounds.w = dbgcomponent->size.w;
    bounds.h = dbgcomponent->size.h;

    SDL_RenderDrawRect (renderer, &bounds);
};


/*
TODO: 
*/
void draw_dbgcomponent_test (SDL_Renderer* renderer, SSGDbgcomponent* dbgcomponent){
    SDL_SetRenderDrawColor (renderer,
                            dbgcomponent->color.r,
                            dbgcomponent->color.g,
                            dbgcomponent->color.b,
                            dbgcomponent->color.a);
    SDL_Rect bounds;
    bounds.x = dbgcomponent->pos.x;
    bounds.y = dbgcomponent->pos.y;
    bounds.w = dbgcomponent->size.w;
    bounds.h = dbgcomponent->size.h;
    SDL_RenderDrawLine (renderer, bounds.x, bounds.y, bounds.x+bounds.w, bounds.y+bounds.h);
    SDL_RenderDrawLine (renderer, bounds.x+bounds.w, bounds.y, bounds.x, bounds.y+bounds.h);
};

/*
TODO: 
*/
void update_dbgcomponent (SDL_Event* event, SSGDbgcomponent* dbgcomponent){

    // Mouse click coords from event handler.
    SDL_Point mousePosition;
    mousePosition.x = event->motion.x; 
    mousePosition.y = event->motion.y;

    //  Moving with cursor.
    if (dbgcomponent->moving) {
        dbgcomponent->pos.x = mousePosition.x;
        dbgcomponent->pos.y = mousePosition.y;
    }

    // Limits from dbgcomponent component.
    SDL_Rect limits;
    limits.x = dbgcomponent->pos.x;
    limits.y = dbgcomponent->pos.y;
    limits.w = dbgcomponent->size.w;
    limits.h = dbgcomponent->size.h;

    if (SDL_PointInRect(&mousePosition, &limits)) {
        switch(event->type)
        {
            case SDL_MOUSEBUTTONDOWN:
                // Change draw function of  dbgcomponent component.
                if (event->button.button == SDL_BUTTON_MIDDLE) {
                    if (dbgcomponent->draw == (PTR_DRAW) &draw_dbgcomponent) {
                        dbgcomponent->draw = (PTR_DRAW) &draw_dbgcomponent_test;
                    } else {
                        dbgcomponent->draw = (PTR_DRAW) &draw_dbgcomponent;
                    }
                }

                // Check moving behaviour.
                if (event->button.button == SDL_BUTTON_LEFT) {
                    dbgcomponent->moving = true;
                    dbgcomponent->point = (Position){mousePosition.x, mousePosition.y};
                    dbgcomponent->color.a = 180;
                }

                // Change the color.
                dbgcomponent->color.r = 0xFF;
                dbgcomponent->color.g = 0x00;
                break;
            
            case SDL_MOUSEBUTTONUP:
                // Release and drop the dbgcomponent component.
                dbgcomponent->moving = false;
                dbgcomponent->color.a = 0xFF;

                // Change color.
                dbgcomponent->color.r = 0x00;
                dbgcomponent->color.g = 0xFF;
                break;
            
            default:
                break;
        }
    }
};

/*
   new_dbgcomponent()
*/
SSGDbgcomponent* new_dbgcomponent () {
    SSGDbgcomponent* new = malloc(sizeof(SSGDbgcomponent));
    new->dad = NULL;
    new->son = NULL;
    return new;
}

/*
    init_dbgcomponent ()
    For a dbgcomponent initialization test.
*/
void init_dbgcomponent  (SSGDbgcomponent* dbgcomponent){
    dbgcomponent->type = SSG_BASIC;
    // dbgcomponent->dad = ...;
    // dbgcomponent->son = NULL;
    dbgcomponent->update = (PTR_UPDATE) &update_dbgcomponent;
    dbgcomponent->draw = (PTR_DRAW) &draw_dbgcomponent;

    dbgcomponent->pos = (Position) {10,100};
    dbgcomponent->size = (Size) {200,30};
    dbgcomponent->color = (Color) {0x00, 0x00, 0xFF, 0xFF};

    dbgcomponent->moving = false;
};

/*
TODO: 
*/
void free_dbgcomponent (SSGDbgcomponent* dbgcomponent){
    if (dbgcomponent->son == NULL) {
        // Break the link with his father and then...
        dbgcomponent->son = NULL;
        // ...be free.
        free (dbgcomponent);
    }
    // TODO: ...else {free first his own son}.
};
