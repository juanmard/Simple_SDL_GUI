#ifndef SSG_SLIDER_H
#define SSG_SLIDER_H

#include <SDL2/SDL.h>
#include "ssg_types.h"

typedef struct ssg_slider SSGSlider;
//typedef void (*ptr_draw_slider)(SDL_Renderer*, SSGSlider*);

/*
TODO: Description
 */
struct ssg_slider
{
    TypeComponent type;
    ptr_update update;
    ptr_draw   draw;
    Position   pos;
    Size       size;
    Color      color;
    void*      dad;
    void*      son;

    int min_value;
    int max_value;
    int value;
    
    // Graphics part.
    // ptr_draw_slider draw;

    // TODO: Convert in Position and Size for not depend of SDL.
    SDL_Rect cursor;
    // TODO: Define an own true-false.
    SDL_bool moving;
    SDL_Point set;
};

SSGSlider*  new_slider (void);
void        init_slider (SSGSlider* slider);
void        free_slider (SSGSlider* slider);

void        draw_slider (SDL_Renderer* renderer, SSGSlider* slider);
void        draw_slider_v2 (SDL_Renderer* renderer, SSGSlider* slider);
void        update_slider (SDL_Event* event, SSGSlider* slider);

#endif
