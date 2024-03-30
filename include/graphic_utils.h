#ifndef GRAPHIC_UTILS_H
#define GRAPHIC_UTILS_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/*
   This file and graphic_utils.c are all helpful functions regarding the
   pixels of the window and their colours
 */
Uint32 getpixel(SDL_Surface *surface, int x, int y);
void getRGB(SDL_Surface *surface, int x, int y, SDL_Color *c);
void print_background(SDL_Renderer* renderer);

#endif
