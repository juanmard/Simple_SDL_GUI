/*
  A debug component for testing behavior.
*/
#include "ssg_dbgcomponent.h"

/*
TODO: 
*/
void draw_dbgcomponent (SDL_Renderer* renderer, SSGDbgcomponent* this){
    // Update cursor.
    if ( (!this->moving) && (!this->sizing) ) {
        switch (this->sizing_state) {
            case NOT_SIZING:
                SDL_SetCursor(this->def_cursor);
                break;
            case NWSE_SIZING:
                SDL_SetCursor(this->nwse_cursor);
                break;
            case WE_SIZING:
                SDL_SetCursor(this->we_cursor);
                break;
            case NS_SIZING:
                SDL_SetCursor(this->ns_cursor);
                break;
        }
    }   
    
    // Draw rect with color.
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

    // Limits.
    SDL_Rect limits;

    //  Moving with cursor.
    if (event->type == SDL_MOUSEMOTION){
        SDL_MouseMotionEvent* eMouse = &(event->motion);
        // Change component.
        if (this->moving) {
            this->pos.x = eMouse->x - this->offset.x;
            this->pos.y = eMouse->y - this->offset.y;
        }
        if (this->sizing){
            switch (this->sizing_state)
            {
                case WE_SIZING:
                    this->size.w = eMouse->x - this->pos.x;
                    break;
                case NS_SIZING:
                    this->size.h = eMouse->y - this->pos.y;
                    break;
                case NWSE_SIZING:
                    this->size.w = eMouse->x - this->pos.x;
                    this->size.h = eMouse->y - this->pos.y;
                    break;
                default:
                    break;
            }
        }

        // Change cursor.
        // TODO: A function that get this check position.
        mousePosition.x = eMouse->x;
        mousePosition.y = eMouse->y;
        limits.x = this->pos.x + this->size.w;
        limits.y = this->pos.y;
        limits.w = SSG_GAP;
        limits.h = this->size.h + SSG_GAP;
        SDL_bool size_w = SDL_PointInRect(&mousePosition, &limits);
        limits.x = this->pos.x;
        limits.y = this->pos.y + this->size.h;
        limits.w = this->size.w + SSG_GAP;
        limits.h = SSG_GAP;
        SDL_bool size_h = SDL_PointInRect(&mousePosition, &limits);

        if ( (!this->moving) && (!this->sizing) ) {
            if (!size_w && !size_h) {
                this->sizing_state = NOT_SIZING;
            } else if (size_w && size_h) {
                this->sizing_state = NWSE_SIZING;
            } else if (size_w) {
                this->sizing_state = WE_SIZING;
            } else if (size_h){
                this->sizing_state = NS_SIZING;
            }
        }        
    }

    if (event->type == SDL_MOUSEBUTTONUP) {
        // Release and drop this component.
        this->moving = false;
        this->sizing = false;

        // Change color.
        this->color.r = 0x00;
        this->color.g = 0xFF;
    }

    // Limits from this component.
    limits.x = this->pos.x;
    limits.y = this->pos.y;
    limits.w = this->size.w + SSG_GAP;
    limits.h = this->size.h + SSG_GAP;
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
                    if (this->sizing_state == NOT_SIZING) {
                        this->moving = true;
                        SDL_SetCursor (this->mov_cursor);
                    } else {
                        this->sizing = true;
                    }
                    this->offset = (Position){eMButton->x - this->pos.x, eMButton->y - this->pos.y};
                }

                // Change the color.
                this->color.r = 0xFF;
                this->color.g = 0x00;
                break;
            
            case SDL_MOUSEBUTTONUP:
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
    return new;
}

/*
    init_dbgcomponent ()
    For a dbgcomponent initialization test.
*/
void init_dbgcomponent  (SSGDbgcomponent* this){
    this->type = SSG_DBGCOMPONENT;
    this->update = (PTR_UPDATE) &update_dbgcomponent;
    this->draw = (PTR_DRAW) &draw_dbgcomponent;

    this->pos = (Position) {10,100};
    this->size = (Size) {200,30};
    this->color = (Color) {0x00, 0x00, 0xFF, 0xFF};

    this->moving = false;
    this->sizing = false;
    this->offset = (Position) {0,0};

    // TODO: Move another global place for all components.
    this->def_cursor = SDL_GetCursor();
    this->mov_cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
    this->we_cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEWE);
    this->ns_cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZENS);
    this->nwse_cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZENWSE);
    this-> sizing_state = NOT_SIZING;
};

/*
TODO: 
*/
void free_dbgcomponent (SSGDbgcomponent* this) {
        SDL_FreeCursor(this->def_cursor);
        SDL_FreeCursor(this->mov_cursor);
        SDL_FreeCursor(this->we_cursor);
        SDL_FreeCursor(this->ns_cursor);
        SDL_FreeCursor(this->nwse_cursor);
        free (this);
};
