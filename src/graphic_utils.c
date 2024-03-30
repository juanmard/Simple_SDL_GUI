#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/*
   getpixel()
   This function returns a Uint32 which represents the colour of the
   pixel in the coordinates (x,y) in the SDL_Surface* surface.
   To be honest, I DIDN'T code this function, if I find its author
   on the Internet, I'll write their name here
 */
Uint32 getpixel(SDL_Surface* surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch (bpp)
    {
    case 1:
        return *p;
        break;

    case 2:
        return *(Uint16 *)p;
        break;

    case 3:
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
        {
            return p[0] | p[1] << 8 | p[2] << 16;
            break;
        }

        case 4:
            return *(Uint32 *)p;
            break;

        default:
            return 0;
      }
}

/*
   getRGB()
   This function copies the colour of the pixel at the coordinates
   (x,y) in the SDL_Surface* surface to the SDL_Color pointed to by c
   To be honest, I DIDN'T code this function, if I find its author
   on the Internet, I'll write their name here
 */
void getRGB(SDL_Surface* surface, int x, int y, SDL_Color *c)
{
    Uint32 data = getpixel(surface,x,y);
    SDL_GetRGB(data,surface->format,&(c->r),&(c->g),&(c->b));
}

/*
   print_background()
   This function fills this SDL_Renderer* renderer with the colour
   grey. It is a little hard-coded regarding the dimensions of the
   window, I should fix that
 */
void print_background(SDL_Renderer* renderer)
{
    SDL_Color rgb;
    SDL_GetRenderDrawColor(renderer, &rgb.r, &rgb.g, &rgb.b, &rgb.a);
    SDL_SetRenderDrawColor(renderer, 0x88, 0x88, 0x88, 0xFF);
    for (int i = 0; i<420; i++)
    {
        SDL_RenderDrawLine(renderer, 0, i, 640, i);
    }
    SDL_SetRenderDrawColor(renderer, rgb.r, rgb.g, rgb.b, rgb.a);
}
