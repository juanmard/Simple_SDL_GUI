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
};
typedef struct ssg_slider SSGSlider;

SSGSlider*  new_slider (void);
void        init_slider (SSGSlider* slider);
void        free_slider (SSGSlider* slider);

void        draw_slider (SDL_Renderer* renderer, SSGSlider* slider);


#endif
