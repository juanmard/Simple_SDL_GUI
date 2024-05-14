/*
TODO: Description.
*/
#include <SDL2/SDL.h>

#include "ssg_slider.h"

void recalculate_cursor_position (SSGSlider* slider) {
    float scale = (float) slider->value / (float) (slider->max_value - slider->min_value);
    float cursor_x = slider->pos.x +  (int) (scale * (float) slider->size.w);
    slider->cursor.x = cursor_x - (slider->cursor.w/2);
}

SSGSlider* new_slider () {
    SSGSlider* slider = malloc (sizeof(SSGSlider));
    init_slider  (slider);
    return slider;
};

void init_slider (SSGSlider* slider){
    slider->type = SSG_SLIDER;
    slider->pos = (Position) {250,320};
    slider->size = (Size) {200,30};
    slider->color = (Color) {0x00, 0x00, 0xFF ,0xFF};

    // Init draw function.
    slider->draw = (PTR_DRAW) &draw_slider;
    slider->update = (PTR_UPDATE) &update_slider;

    // Test...
    slider->min_value = 0;
    slider->max_value = 100;
    slider->value = 10;

    // Other...
    slider->moving = SDL_FALSE;

    // Cursor....
    slider->cursor.w = 10;
    slider->cursor.h = slider->size.h;
    slider->cursor.y  = slider->pos.y;
    recalculate_cursor_position (slider);
};

/*
TODO: Description and implementation.
*/
void free_slider (SSGSlider* slider){
    free (slider);
};

/*
TODO: Description.
*/
void draw_slider (SDL_Renderer* renderer, SSGSlider* slider){
    SDL_SetRenderDrawColor (renderer,
                            slider->color.r,
                            slider->color.g,
                            slider->color.b,
                            slider->color.a);
    // Central line.
    SDL_RenderDrawLine (renderer,
                        slider->pos.x, slider->pos.y + slider->size.h/2,
                        slider->pos.x + slider->size.w, slider->pos.y + slider->size.h/2);
    // Cursor.
    if (slider->moving) SDL_SetRenderDrawColor (renderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderDrawRect (renderer, &(slider->cursor));
};

void draw_slider_v2 (SDL_Renderer* renderer, SSGSlider* slider){
    SDL_SetRenderDrawColor (renderer,
                            slider->color.r,
                            slider->color.g,
                            slider->color.b,
                            slider->color.a);
    // Central line.slider
// TODO: A converter {Position,Size} in a {SDL_Rect}.
    SDL_Rect bounds;
    bounds.x = slider->pos.x;
    bounds.y = slider->pos.y;
    bounds.w = slider->size.w;
    bounds.h = slider->size.h;
    SDL_RenderDrawRect (renderer, &bounds);

    // Cursor.
    if (slider->moving) SDL_SetRenderDrawColor (renderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderDrawRect (renderer, &(slider->cursor));
};

void update_slider (SDL_Event* event, SSGSlider* slider){
    // Mouse click coords from event handler.
    SDL_Point mousePosition;
    mousePosition.x = event->motion.x; 
    mousePosition.y = event->motion.y;

    // Limits from basic component.
    SDL_Rect limits;
    limits.x = slider->pos.x;
    limits.y = slider->pos.y;
    limits.w = slider->size.w;
    limits.h = slider->size.h;

    // If the event is on slider...
    // TODO: A boolean saying "no filter" and receive all events.
    if (SDL_PointInRect(&mousePosition, &limits)) {
        // Update "value" if  moving cursor.
        if (slider->moving) {
            float scale = (float) (slider->max_value - slider->min_value) / (float)  slider->size.w;
            slider->value += scale * (mousePosition.x - slider->set.x);
            slider->set = mousePosition;
            //slider->cursor.x = mousePosition.x;
        }

        // Update cursor position.
        // TODO: in "change_value ()" get a "change" bool for recalculate.
        //       if (change_value) { recalculate_cursor };
        recalculate_cursor_position (slider);

        // Update with event.
        switch(event->type)
        {
            case SDL_MOUSEBUTTONDOWN:
                if (SDL_PointInRect(&mousePosition, &(slider->cursor)) &
                    (slider->moving == SDL_FALSE) )
                {
                    slider->moving = SDL_TRUE;
                    slider->set = mousePosition;
                }

                // TODO: Create slider->inc_value() and check max_value on it.
                if (event->button.button == SDL_BUTTON_LEFT) {
                    if (mousePosition.x > slider->cursor.x){
                        if ((slider->value++) > (slider->max_value)) slider->value = slider->max_value;
                    } else {
                        if ((slider->value--) < (slider->min_value)) slider->value = slider->min_value;
                    }
                }
                
                // Change draw function.
                if (event->button.button == SDL_BUTTON_MIDDLE) {
                    if (slider->draw == (PTR_DRAW) &draw_slider) {
                        slider->draw = (PTR_DRAW) &draw_slider_v2;
                    } else {
                        slider->draw = (PTR_DRAW) &draw_slider;
                    }
                }
                break;

            case SDL_MOUSEBUTTONUP:
                slider->moving = SDL_FALSE;
                break;

            default:
                break;
        }
    }
};
