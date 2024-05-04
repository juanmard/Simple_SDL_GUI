#ifndef SSG_SLIDER_H
#define SSG_SLIDER_H

#include "ssg_component.h"

/*
TODO: Description
 */
struct ssg_slider
{
    SSGComponent* dad;

    int min_value;
    int max_value;
    int value;
    
    // TODO: Convert in Position and Size for not depend of SDL.
    SDL_Rect cursor;
    // TODO: Define an own true-false.
    SDL_bool moving;
    SDL_Point set;
};
typedef struct ssg_slider SSGSlider;

SSGSlider*  new_slider (void);
void        init_slider (SSGSlider* slider);
void        free_slider (SSGSlider* slider);

void        draw_slider (SDL_Renderer* renderer, SSGSlider* slider);
void        update_slider (SDL_Event* event, SSGSlider* slider);

#endif
