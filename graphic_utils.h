#ifndef GRAPHIC_UTILS_H
#define GRAPHIC_UTILS_H

Uint32 getpixel(SDL_Surface *surface, int x, int y);
void getRGB(SDL_Surface *surface, int x, int y, SDL_Color *c);

#endif
