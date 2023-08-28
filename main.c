#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <err.h>
#include <stddef.h>

#include "graphic_utils.h"
#include "ssg_button.h"
#include "ssg_text.h"
#include "ssg_menu.h"
#include "ssg_menu_list.h"
#include "welcome.h"
#include "hall.h"
#include "ssg_debug_text.h"

const int INIT_WIDTH = 640;
const int INIT_HEIGHT = 400;

void draw(SDL_Renderer* renderer)
{
    SDL_RenderPresent(renderer);
}

void event_loop(SDL_Renderer* renderer,
                struct ssg_menu_list* menu_list,
                //struct ssg_menu_list* sub_menu_list,
                struct ssg_debug_text* curr_menu_pointer,
                SDL_Surface* font)
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
                print_menu(renderer, menu_list->menu, font);
                // the "multiple-menus-being-displayed-at-the-same-
                // time" problem's cause  might be here
                //print_menu(renderer, sub_menu_list->menu, font);
                update_menu_name_pointer(curr_menu_pointer, menu_list);
                print_ssg_debug_text(renderer, curr_menu_pointer,font);
                draw(renderer);
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            if(event.button.button == SDL_BUTTON_LEFT)
            {
                if(mbl_pushed)
                    break;
                mbl_pushed = 1;
                check_button(menu_list, menu_list->menu,
                             event.button.x, event.button.y,
                             renderer);
            }
            break;
        case SDL_MOUSEBUTTONUP:
            if(event.button.button == SDL_BUTTON_LEFT)
                mbl_pushed = 0;
        default:
            break;
        }
        print_background(renderer);
        print_menu(renderer, menu_list->menu, font);
        //print_menu(renderer, sub_menu_list->menu, font);
        update_menu_name_pointer(curr_menu_pointer, menu_list);
        print_ssg_debug_text(renderer, curr_menu_pointer,font);
        draw(renderer);
    }
}

int main()//int argc, char** argv)
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0)
        errx(EXIT_FAILURE, "%s", SDL_GetError());

    /*
    SDL_Window* window = SDL_CreateWindow("Image", 0, 0, INIT_WIDTH,
              INIT_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    */
    SDL_Window* window = SDL_CreateWindow("SSG - Tests", 0, 0,
                          INIT_WIDTH, INIT_HEIGHT, SDL_WINDOW_SHOWN);

    if(window == NULL)
        errx(EXIT_FAILURE, "%s", SDL_GetError());

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1,
                                      SDL_RENDERER_ACCELERATED);

    if(renderer == NULL)
        errx(EXIT_FAILURE, "%s", SDL_GetError());

    SDL_Surface* font = IMG_Load("font1.png");

    // MENU LIST
    struct ssg_menu_list* menu_list = new_menu_list();

    // MENU 1
    struct ssg_menu* menu1 = add_menu(menu_list, "Welcome!");

    // MENU 2
    struct ssg_menu* menu2 = add_menu(menu_list, "The Hall");

    // BUTTON 1
    struct ssg_button* button_1 = new_button_std(250, 50, "pink_button\
", 0xFF, 0x00, 0x55, "PINK BUTTON");

    // BUTTON 2
    struct ssg_button* button_2 = new_button_std(250, 120, "cian_\
button", 0x22, 0x44, 0xBB, "ANOTHER BUTTON");

    // BUTTON 3
    struct ssg_button* button_3 = new_button_std(250, 190, "orange_\
button", 0xDD, 0x77, 0x00, "ORANGE BUTTON");

    // BUTTON 4
    struct ssg_button* button_4 = new_button_std(250, 120, "red_\
button", 0x9F, 0x08, 0x08, "RED BUTTON");

    // BUTTON 5
    struct ssg_button* button_5 = new_button_std(250, 50, "black_\
button", 0x33, 0x33, 0x33, "black BUTTON");

    /*
      BUTTON LIST (we use directly "add to menu" instead of "add to
      list")
     */
    add_button_to_menu(menu1, button_1); // pink
    add_button_to_menu(menu1, button_2); // another
    add_button_to_menu(menu1, button_3); // orange
    add_button_to_menu(menu2, button_4); // red
    add_button_to_menu(menu2, button_5); // black

    // TEXT 1
    struct ssg_text* text1 = new_ssg_text(350, 50, 180, 160,
           0x11, 0xFF, 0x33, "Press this pink button to go to The \
Hall");

    // TEXT 2
    struct ssg_text* text2 = new_ssg_text(350, 170, 200, 140,
                                          0x00, 0xBB, 0xFF, "!\"#$%&'(\
)*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklm\
nopqrstuvwxyz{|}~");

    // TEXT 3
    struct ssg_text* text3 = new_ssg_text(3, 10, 70, 50,
                                          0x99, 0x99, 0x99, "Escribe\
 texto aqui");

    // TEXT LIST 1
    add_text_to_menu(menu1, text1); // press to go
    add_text_to_menu(menu2, text2); // te envio
    add_text_to_menu(menu2, text3); // escribe texto aqui

    /*
       MENU 1: pink, another, orange
               matrix
       MENU 2: red, black
               te envio, escribe texto aqui
     */

    // MENU LIST 2 sub_menu
    /*
    struct ssg_menu_list* sub_menu_list = new_menu_list();
    struct ssg_menu* sub_menu1 = add_menu(sub_menu_list, "Sub-Menu");
    struct ssg_button* sub_button1 =
        new_button_std(360, 50, "sub_button1_name", 0xFF, 0xFF,
                       0xFF, "Sub");
    add_button_to_menu(sub_menu1, sub_button1);
    */

    // DEBUG TEXT 1
    /*
      For the moment, let's just work with one ssg_debug_text, instead
      of including it in a "ssg_debug_text_list" (which doesn't exist
      for the moment), and even including this list into a "ssg_menu_
      debug_list" (which doesn't exist neither)
     */
    struct ssg_debug_text* curr_menu_pointer =
        new_ssg_debug_text(490, 0, 150, 16, 0xFF, 0xFF, 0xFF, pointer,
                           &menu_list->menu->name);

    enable_menu(menu_list, menu1);
    //printf("Antes de pintar\n");
    /*
    print_background(renderer);
    draw(renderer);
    */
    print_background(renderer);
    draw(renderer);
    //printf("Despues de pintar\n");

    //enable_menu(sub_menu_list, sub_menu1);

    event_loop(renderer, menu_list, //sub_menu_list,
               curr_menu_pointer, font);

    //free_menu_list(sub_menu_list);
    free_debug_text(curr_menu_pointer);
    free_menu_list(menu_list);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_FreeSurface(font);
    SDL_Quit();

    return EXIT_SUCCESS;
}
