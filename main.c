#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <err.h>
#include <stddef.h>

#include "graphic_utils.h"
#include "ssg_button.h"
#include "ssg_text.h"
#include "ssg_menu.h"
#include "welcome.h"

const int INIT_WIDTH = 640;
const int INIT_HEIGHT = 400;

void draw(SDL_Renderer* renderer)
{
    SDL_RenderPresent(renderer);
}



void event_loop(SDL_Renderer* renderer,
                struct ssg_button_list* button_list1,
                struct ssg_text* text1,
                struct ssg_text* text2)
{
    SDL_Event event;
    event.type = SDL_WINDOWEVENT;
    int mbl_pushed = 0;
    while(1)
    {
        SDL_WaitEventTimeout(&event,20);
        switch(event.type)
        {
        case SDL_QUIT:
            return;
        case SDL_WINDOWEVENT:
            if(event.window.event == SDL_WINDOWEVENT_RESIZED)
            {
                print_button_list(renderer, button_list1);
                print_ssg_text(renderer, text1);
                print_ssg_text(renderer, text2);
                draw(renderer);
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            if(event.button.button == SDL_BUTTON_LEFT)
            {
                if(mbl_pushed)
                    break;
                mbl_pushed = 1;
                check_pressed_buttons(button_list1, event.button.x,
                                      event.button.y);
            }
            break;
        case SDL_MOUSEBUTTONUP:
            if(event.button.button == SDL_BUTTON_LEFT)
                mbl_pushed = 0;
        default:
            break;
        }
        print_button_list(renderer, button_list1);
        print_ssg_text(renderer, text1);
        print_ssg_text(renderer, text2);
        draw(renderer);
    }
}

int main(int argc, char** argv)
{
    printf("Hello World, here starts the main\n");

    if(SDL_Init(SDL_INIT_VIDEO) != 0)
        errx(EXIT_FAILURE, "%s", SDL_GetError());

    SDL_Window* window = SDL_CreateWindow("Image", 0, 0, INIT_WIDTH,
              INIT_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

    if(window == NULL)
        errx(EXIT_FAILURE, "%s", SDL_GetError());

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1,
                                      SDL_RENDERER_ACCELERATED);

    if(renderer == NULL)
        errx(EXIT_FAILURE, "%s", SDL_GetError());



    // BUTTON 1
    struct ssg_button* button_1 = new_button_std(350, 50, "pink_button\
", 0xFF, 0x00, 0x55, "PINK BUTTON");

    // BUTTON 2
    struct ssg_button* button_2 = new_button_std(200, 50, "cian_\
button", 0x22, 0x44, 0xBB, "ANOTHER BUTTON");

    // BUTTON 3
    struct ssg_button* button_3 = new_button_std(275, 120, "orange_\
button", 0xDD, 0x77, 0x00, "ORANGE BUTTON");

    // BUTTON 3
    struct ssg_button* button_4 = new_button_std(300, 250, "red_\
button", 0xEE, 0x10, 0x10, "RED BUTTON");


    /*
      BUTTON LIST
     */
    struct ssg_button_list* button_list1 = new_button_list();
    add_button_to_list(button_list1, button_1);
    add_button_to_list(button_list1, button_2);
    add_button_to_list(button_list1, button_3);
    add_button_to_list(button_list1, button_4);

    // TEXT 1
    struct ssg_text* text1 = new_ssg_text(50, 250, 160, 160,
           0x11, 0xFF, 0x33, "The Matrix es una pelicula de mil \
novecientos noventa y nueve dirigida por los antiguamente conocidos \
como los hermanos Wachosky");

    // TEXT 2
    struct ssg_text* text2 = new_ssg_text(350, 170, 200, 140,
                                          0x00, 0xBB, 0xFF, "Te envio\
 poemas de mi puno y letra te envio canciones de cuatro cuarenta");


    event_loop(renderer, button_list1, text1, text2);

    free_text(text1);
    free_text(text2);
    free_button_list(button_list1);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();

    return EXIT_SUCCESS;
}
