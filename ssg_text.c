#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <time.h>

#include "graphic_utils.h"
#include "ssg_text.h"

#define SSG_TEXT_LIMIT 240 // is this too much?

void print_letter(SDL_Renderer* renderer, char* letter, int x, int y,
                  SDL_Surface* font)
{
    // first we find out the position of the letter in the font image
    char let = *letter;
    int x_font = 0, y_font = 1;
    if (let <= 'Z')
        y_font += 9*3 + 3;
    else if (let > 'Z')
        let -= ('a' - 'A');
    x_font = let - 65;
    if (x_font >= 14)
        x_font++;
    x_font %= 9;
    x_font = 1 + 7*x_font;

    switch (let)
    {
    case 'J':
    case 'K':
    case 'L':
    case 'M':
    case 'N':
    //case 'Ñ':
    case 'O':
    case 'P':
    case 'Q':
        y_font += 10;
        break;
    case 'R':
    case 'S':
    case 'T':
    case 'U':
    case 'V':
    case 'W':
    case 'X':
    case 'Y':
    case 'Z':
        y_font += 20;
        break;
    }

    // now we copy the letter into the renderer
    for (size_t i = 0; i<6; i++)
    {
        for (size_t j = 0; j<9; j++)
        {
            SDL_Color c;
            getRGB(font, x_font+i, y_font+j, &c);
            if (c.r < 80)
                SDL_RenderDrawPoint(renderer, x+i, y+j);
        }
    }

}

void print_ssg_text(SDL_Renderer* renderer, struct ssg_text* text)
{
    SDL_Surface* font = IMG_Load("font1.png");
    SDL_Color clr;
    clr.r = text->red;
    clr.g = text->green;
    clr.b = text->blue;
    clr.a = 0xFF;

    SDL_Color render_color;
    SDL_GetRenderDrawColor(renderer, &render_color.r, &render_color.g,
                           &render_color.b, &render_color.a);
    SDL_SetRenderDrawColor(renderer, clr.r, clr.g, clr.b, clr.a);

    int letters_per_row = text->w/7;
    int letters_per_col = text->h/10;

    char* curr_let = text->text;

    for (int j = 0; j<letters_per_col; j++)
    {
        if (!*curr_let)
            break;
        for (int i = 0; i<letters_per_row; i++)
        {
            if (!*curr_let)
                break;
            if (*curr_let == ' ')
            {
                curr_let++;
                continue;
            }
            print_letter(renderer, curr_let, text->x+(i*7),
                         text->y+(j*10), font);
            curr_let++;
        }
    }
    SDL_SetRenderDrawColor(renderer, render_color.r, render_color.g,
                           render_color.b, render_color.a);
    SDL_FreeSurface(font);
}

void free_text(struct ssg_text* text)
{
    /* frees the memory in which the ssg_text is allocated
     */
    free(text->text);
    free(text);
}

struct ssg_text* new_ssg_text(int x, int y, int w, int h,
                              int red, int green, int blue,
                              char* text)
{
    struct ssg_text* new_text = malloc(sizeof(struct ssg_text));
    new_text->text = malloc(sizeof(char) * SSG_TEXT_LIMIT);
    strncpy(new_text->text, text, SSG_TEXT_LIMIT);
    *(new_text->text + SSG_TEXT_LIMIT - 1) = 0;
    new_text->x = x;
    new_text->y = y;
    new_text->w = w;
    new_text->h = h;
    new_text->red = red;
    new_text->green = green;
    new_text->blue = blue;

    return new_text;
}
