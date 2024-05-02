#include "ssg_gui.h"

#define INIT_WIDTH 640
#define INIT_HEIGHT 400

struct ssg_gui *init_gui(char *window_name)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "ERROR: %s\n", SDL_GetError());
        return NULL;
    }

    SDL_StartTextInput();

    SDL_Window* window = SDL_CreateWindow(window_name, 0, 0, INIT_WIDTH,
            INIT_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window)
    {
        fprintf(stderr, "ERROR: SDL_Window: %s\n", SDL_GetError());
        SDL_Quit();
        return NULL;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1,
            SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    }

    if (!renderer)
    {
        fprintf(stderr, "ERROR: SDL_Renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return NULL;
    }

    struct ssg_menu_list *menu_list = new_menu_list();
    if (!menu_list)
    {
        fprintf(stderr, "ERROR: Couldn't allocate the new menu_list\n");
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return NULL;
    }

    struct ssg_gui *new = malloc(sizeof(struct ssg_gui));
    if (!new)
    {
        fprintf(stderr, "ERROR: Couldn't malloc() the new ssg_gui\n");
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return NULL;
    }

    new->window = window;
    new->renderer = renderer;
    new->menu_list = menu_list;
    new->font = NULL;

    return new;
}

int set_font(struct ssg_gui *gui, char *filename)
{
    SDL_Surface *font = IMG_Load(filename);
    if (!font)
    {
        fprintf(stderr, "ERROR: Couldn't load font %s\n", filename);
        return -1;
    }

    gui->font = font;
    return 0;
}

void close_gui(struct ssg_gui *gui)
{
        SDL_DestroyRenderer(gui->renderer);
        SDL_DestroyWindow(gui->window);
        SDL_StopTextInput();
        SDL_Quit();
        if (gui->font)
        {
            SDL_FreeSurface(gui->font);
        }
        free_menu_list(gui->menu_list);
        free(gui);
}

void print_components (struct ssg_gui *gui){
    if (gui->components != NULL){
        SSGComponent* test = gui->components->component;
        (test->draw)(gui->renderer,test);
    }
};