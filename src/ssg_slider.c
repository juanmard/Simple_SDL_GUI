/*
TODO: Description.
*/
#include <SDL2/SDL.h>

#include "ssg_slider.h"

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
    new_dad->pos = (Position) {250,300};
    new_dad->size = (Size) {100,15};
    new_dad->color = (Color) {0x00, 0x00, 0xFF ,0xFF};
//    new_dad->update = NULL;
    slider->dad = new_dad;

    // Test...
    slider->min_value = 0;
    slider->max_value = 100;
    slider->value = 30;
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
    SDL_RenderDrawLine (renderer,
                        comp->pos.x, comp->pos.y + comp->size.h/2,
                        comp->pos.x + comp->size.w, comp->pos.y + comp->size.h/2);
};
