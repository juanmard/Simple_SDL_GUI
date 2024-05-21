/*
TODO: Description.
*/
#include <SDL2/SDL.h>

#include "ssg_label.h"

SSGLabel* new_label () {
    SSGLabel* label = malloc (sizeof(SSGLabel));
    init_label  (label);
    return label;
};

void init_label (SSGLabel* this){
    this->type = SSG_LABEL;
    this->pos = (Position) {10,100};
    this->size = (Size) {200,30};
    this->color = (Color) {0xFF, 0x00, 0x00, 0xFF};

    // Init draw function.
    this->draw = (PTR_DRAW) &draw_label;
    this->update = (PTR_UPDATE) &update_label;

    // Debug text label.
    this->text = "Debug text label";
    // This opens a font style and sets a size
    this->font = TTF_OpenFont("lazy.ttf", 24);
};

/*
TODO: Description and implementation.
*/
void free_label (SSGLabel* this){
    free (this);
};

/*
TODO: Description.
*/
void draw_label (SDL_Renderer* renderer, SSGLabel* this){
    // this is the color in rgb format,
    // maxing out all would give you the color white,
    // and it will be your text's color
    SDL_Color White = {255, 255, 255};

    // as TTF_RenderText_Solid could only be used on
    // SDL_Surface then you have to create the surface first
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid (this->font, this->text, White); 

    // now you can convert it into a texture
    SDL_Texture* Message = SDL_CreateTextureFromSurface (renderer, surfaceMessage);

    SDL_Rect Message_rect; //create a rect
    Message_rect.x = this->pos.x;  //controls the rect's x coordinate 
    Message_rect.y = this->pos.y; // controls the rect's y coordinate
    Message_rect.w = this->size.w; // controls the width of the rect
    Message_rect.h = this->size.h; // controls the height of the rect

    // (0,0) is on the top left of the window/screen,
    // think a rect as the text's box,
    // that way it would be very simple to understand

    // Now since it's a texture, you have to put RenderCopy
    // in your game loop area, the area where the whole code executes

    // you put the renderer's name first, the Message,
    // the crop size (you can ignore this if you don't want
    // to dabble with cropping), and the rect which is the size
    // and coordinate of your texture
    SDL_RenderCopy (renderer, Message, NULL, &Message_rect);

    // Don't forget to free your surface and texture
    //SDL_FreeSurface (surfaceMessage);
    //SDL_DestroyTexture (Message);

    // Draw limits.
    SDL_RenderDrawRect (renderer, &Message_rect);
};

/*
TODO: Description.
*/
void update_label (SDL_Event* event, SSGLabel* this){
    
};
