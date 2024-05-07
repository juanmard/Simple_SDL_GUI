#include "ssg_component.h"

void draw_component (SDL_Renderer* renderer, SSGComponent* component){
    if (component->draw){
        (component->draw)(renderer, component);
    }
};

void update_component (SDL_Event*  event, SSGComponent* component){
    if (component->update){
        (component->update)(event, component);
    }
};

/*
    init_component ()
    For a basic initialization test.
*/
void init_component  (SSGComponent* component){
    component->type = SSG_COMPONENT;
    component->update = NULL;
    component->draw = NULL;
};

/*
   new_component()
*/
SSGComponent* new_component () {
    SSGComponent* new = malloc(sizeof(SSGComponent));
   
    return new;
}

/*
TODO: 
*/
void free_component (SSGComponent* component){
    // TODO: Check if it has a son.
    //       if (son) free_son (son)...
    //if (component->son == NULL){
        free (component);
    //}
};
