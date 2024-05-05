/*
TODO: Description.
*/
#include <SDL2/SDL.h>

#include "ssg_slider.h"

void recalculate_cursor_position (SSGSlider* slider) {
    float scale = (float) slider->value / (float) (slider->max_value - slider->min_value);
    float cursor_x = slider->dad->pos.x +  (int) (scale * (float) slider->dad->size.w);
    slider->cursor.x = cursor_x - (slider->cursor.w/2);
}

SSGSlider* new_slider () {
    SSGSlider* slider = malloc (sizeof(SSGSlider));
    init_slider  (slider);
    return slider;
};

void init_slider (SSGSlider* slider){
    SSGComponent* new_dad = new_component ();
    init_component(new_dad);
    new_dad->son = slider;
    new_dad->type = SSG_SLIDER;
    new_dad->pos = (Position) {250,320};
    new_dad->size = (Size) {200,30};
    new_dad->color = (Color) {0x00, 0x00, 0xFF ,0xFF};
    slider->dad = new_dad;

    // Init draw function.
    slider->draw = &draw_slider;

    // Test...
    slider->min_value = 0;
    slider->max_value = 100;
    slider->value = 70;

    // Other...
    slider->moving = SDL_FALSE;

    // Cursor....
    slider->cursor.w = 10;
    slider->cursor.h = slider->dad->size.h;
    slider->cursor.y  = slider->dad->pos.y;
    recalculate_cursor_position (slider);
};

/*
TODO: Description and implementation.
*/
void free_slider (SSGSlider* slider){

};

/*
TODO: Description.
*/
void draw_slider (SDL_Renderer* renderer, SSGSlider* slider){
    SSGComponent* comp = slider->dad;
    SDL_SetRenderDrawColor (renderer,
                            comp->color.r,
                            comp->color.g,
                            comp->color.b,
                            comp->color.a);
    // Central line.
    SDL_RenderDrawLine (renderer,
                        comp->pos.x, comp->pos.y + comp->size.h/2,
                        comp->pos.x + comp->size.w, comp->pos.y + comp->size.h/2);
    // Cursor.
    if (slider->moving) SDL_SetRenderDrawColor (renderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderDrawRect (renderer, &(slider->cursor));
};

void draw_slider_v2 (SDL_Renderer* renderer, SSGSlider* slider){
    SSGComponent* comp = slider->dad;
    SDL_SetRenderDrawColor (renderer,
                            comp->color.r,
                            comp->color.g,
                            comp->color.b,
                            comp->color.a);
    // Central line.
    // TODO: A converter {Position,Size} in a {SDL_Rect}.
    SDL_Rect bounds;
    bounds.x = comp->pos.x;
    bounds.y = comp->pos.y;
    bounds.w = comp->size.w;
    bounds.h = comp->size.h;
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

    // Update "value" if  moving cursor.
    if (slider->moving) {
        float scale = (float) (slider->max_value - slider->min_value) / (float)  slider->dad->size.w;
        slider->value += scale * (mousePosition.x - slider->set.x);
        slider->set = mousePosition;
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
                if (slider->draw == &draw_slider) {
                    slider->draw = &draw_slider_v2;
                } else {
                    slider->draw = &draw_slider;
                }
            }
            break;

        case SDL_MOUSEBUTTONUP:
            slider->moving = SDL_FALSE;
            break;

        default:
            break;
    }
};
