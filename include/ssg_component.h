#ifndef SSG_COMPONENT_H
#define SSG_COMPONENT_H

#include <SDL2/SDL.h>
#include "ssg_types.h"
#include "ssg_basic.h"
#include "ssg_slider.h"
#include "ssg_label.h"
#include "ssg_dbgcomponent.h"

//TODO: Change in code all structs definitions for typedef.
typedef union ssg_component SSGComponent;

/*
   A "ssg_component" is a basic object which has a reference
   from how it display (draw) and change (update).
 */
union ssg_component
{   struct {
        TypeComponent type;
        ptr_update    update;
        ptr_draw      draw;
    };
    SSGBasic   basic;
    SSGSlider  slider;
    SSGLabel   label;
    SSGDbgcomponent  dbgcomponent;
};

void           init_component   (SSGComponent* component);
SSGComponent*  new_component    ();
void           free_component   (SSGComponent* component);
void           draw_component   (SDL_Renderer* renderer, SSGComponent* component);
void           update_component (SDL_Event* event, SSGComponent* component);

#endif
