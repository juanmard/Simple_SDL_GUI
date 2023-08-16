#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

Uint32 getpixel(SDL_Surface *surface, int x, int y)
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

void getRGB(SDL_Surface *surface, int x, int y, SDL_Color *c)
{
    Uint32 data = getpixel(surface,x,y);
    SDL_GetRGB(data,surface->format,&(c->r),&(c->g),&(c->b));
}

void print_background(SDL_Renderer* renderer)
{
    SDL_Color rgb;
    SDL_GetRenderDrawColor(renderer, &rgb.r, &rgb.g, &rgb.b, &rgb.a);
    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
    for (int i = 0; i<420; i++)
    {
        SDL_RenderDrawLine(renderer, 0, i, 640, i);
    }
    SDL_SetRenderDrawColor(renderer, rgb.r, rgb.g, rgb.b, rgb.a);
}
