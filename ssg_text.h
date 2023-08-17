#ifndef SSG_TEXT_H
#define SSG_TEXT_H

#define SSG_TEXT_LIMIT 240 // is this too much?

/*
   An ssg_text is an object (not OOP) which has a position (x,y), a
   width, a height, a colour (red, green, blue) and a string text
   which it displays. It also has a size but that field hasn't been
   used yet, since there's only one existing size for the moment
 */
struct ssg_text
{
    int size;
    int x;
    int y;
    int w;
    int h;
    int red;
    int green;
    int blue;
    char* text;
};

void print_letter(SDL_Renderer* renderer, char* letter, int x, int y,
                  SDL_Surface* font);
void print_ssg_text(SDL_Renderer* renderer, struct ssg_text* text,
                    SDL_Surface* font);
void free_text(struct ssg_text* text);
struct ssg_text* new_ssg_text(int x, int y, int w, int h,
                              int red, int green, int blue,
                              char* text);

#endif
