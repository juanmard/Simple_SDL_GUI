#ifndef SSG_TEXT_H
#define SSG_TEXT_H

#define SSG_TEXT_LIMIT 240 // is this too much?

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
