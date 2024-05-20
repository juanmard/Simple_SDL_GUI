/*
  A debug component for testing behavior.
*/
#include "ssg_dbgcomponent.h"

/*
TODO: 
*/
void draw_dbgcomponent (SDL_Renderer* renderer, SSGDbgcomponent* this){
    SDL_SetRenderDrawColor (renderer,
                    this->color.r,
                    this->color.g,
                    this->color.b,
                    this->color.a);
    SDL_Rect bounds;
    bounds.x = this->pos.x;
    bounds.y = this->pos.y;
    bounds.w = this->size.w;
    bounds.h = this->size.h;

    SDL_RenderDrawRect (renderer, &bounds);
};


/*
TODO: 
*/
void draw_dbgcomponent_test (SDL_Renderer* renderer, SSGDbgcomponent* this){
    SDL_SetRenderDrawColor (renderer,
                            this->color.r,
                            this->color.g,
                            this->color.b,
                            this->color.a);
    SDL_Rect bounds;
    bounds.x = this->pos.x;
    bounds.y = this->pos.y;
    bounds.w = this->size.w;
    bounds.h = this->size.h;
    SDL_RenderDrawLine (renderer, bounds.x, bounds.y, bounds.x+bounds.w, bounds.y+bounds.h);
    SDL_RenderDrawLine (renderer, bounds.x+bounds.w, bounds.y, bounds.x, bounds.y+bounds.h);
};

/*
TODO: 
*/
void update_dbgcomponent (SDL_Event* event, SSGDbgcomponent* this) {

    // Mouse click coords from event handler.
    SDL_Point mousePosition;
    mousePosition.x = event->motion.x; 
    mousePosition.y = event->motion.y;

    //  Moving with cursor.
    if (event->type == SDL_MOUSEMOTION){
        SDL_MouseMotionEvent* eMouse = &(event->motion);
        if (this->moving) {
            this->pos.x = eMouse->x - this->offset.x;
            this->pos.y = eMouse->y - this->offset.y;
        }
        if (this->sizing){
            this->size.w = eMouse->x - this->offset.x;
        }
    }

    // Limits from this component.
    SDL_Rect limits;
    limits.x = this->pos.x;
    limits.y = this->pos.y;
    limits.w = this->size.w;
    limits.h = this->size.h;
    if (SDL_PointInRect(&mousePosition, &limits)) {
        switch(event->type)
        {
            case SDL_MOUSEBUTTONDOWN:
                SDL_MouseButtonEvent* eMButton = &(event->button);
                // Change draw function of  this component.
                if (eMButton->button == SDL_BUTTON_MIDDLE) {
                    if (this->draw == (PTR_DRAW) &draw_dbgcomponent) {
                        this->draw = (PTR_DRAW) &draw_dbgcomponent_test;
                    } else {
                        this->draw = (PTR_DRAW) &draw_dbgcomponent;
                    }
                }

                // Check moving and sizing behaviour.
                if (eMButton->button  == SDL_BUTTON_LEFT) {
                    if (eMButton->x > (this->pos.x + this->size.w-2)) {
                        this->sizing = true;
                        this->color.g = 128;
                    } else {
                        this->moving = true;
                        this->color.r = 128;
                    }
                    this->offset = (Position){eMButton->x - this->pos.x, eMButton->y - this->pos.y};
                }

                // Change the color.
                this->color.r = 0xFF;
                this->color.g = 0x00;
                break;
            
            case SDL_MOUSEBUTTONUP:
                // Release and drop the this component.
                this->moving = false;
                this->sizing = false;
                this->color.a = 0xFF;

                // Change color.
                this->color.r = 0x00;
                this->color.g = 0xFF;
                break;
            
            case SDL_MOUSEMOTION:
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
void init_dbgcomponent  (SSGDbgcomponent* this){
    this->type = SSG_DBGCOMPONENT;
    // this->dad = ...;
    // this->son = NULL;
    this->update = (PTR_UPDATE) &update_dbgcomponent;
    this->draw = (PTR_DRAW) &draw_dbgcomponent;

    this->pos = (Position) {10,100};
    this->size = (Size) {200,30};
    this->color = (Color) {0x00, 0x00, 0xFF, 0xFF};

    this->moving = false;
    this->sizing = false;
    this->offset = (Position) {0,0};
};

/*
TODO: 
*/
void free_dbgcomponent (SSGDbgcomponent* this){
    if (this->son == NULL) {
        // Break the link with his father and then...
        this->son = NULL;
        // ...be free.
        free (this);
    }
    // TODO: ...else {free first his own son}.
};
