#include <stdio.h>
#include <pthread.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <err.h>
#include <time.h>

#include "graphic_utils.h"
#include "ssg_button.h"
#include "ssg_menu.h"
#include "ssg_menu_list.h"

/* This is the .c file for the second  menu, which has 2 buttons:
   - the red one prints "ete boton e rojo jeje"
   - the black one prints "ete boton e negro (black in spanish" and
   enables the first menu, named "first menu :)"
 */


/*
   check_pressed_buttons2()
   This function is exactly the same as check_pressed_buttons1(), but
   it handles all the buttons in the second menu instead of the first
   one
 */
void check_pressed_buttons2(struct ssg_menu_list* menu_list,
                            struct ssg_button_list* list, int x, int y,
                            SDL_Renderer* renderer)
{
    struct ssg_button* button;
    if ( (button =
          is_button_pressed_from_name(list, "black_button", x, y)))
    {
        printf("ete boton e negro (black in spanish)\n");

        pthread_t thr;
        int e;
        e = pthread_create(&thr, NULL,
                           button_press_feedback,
                           (void*) button);
        if (e != 0)
            errx(EXIT_FAILURE, "pthread_create()");
        pthread_detach(thr);

        if (renderer)
        {
            print_background(renderer);
            SDL_RenderPresent(renderer);
            print_background(renderer);
            SDL_RenderPresent(renderer);
        }

        if (enable_menu(menu_list, find_menu_name(menu_list,
                                  "Welcome!")))
            errx(EXIT_FAILURE, "enable_menu()");
    }
    if ((button =
         is_button_pressed_from_name(list, "red_button", x, y)))
    {
        printf("ete boton e rojo jeje\n");
        pthread_t thr;
        int e;
        e = pthread_create(&thr, NULL,
                           button_press_feedback,
                           (void*) button);
        if (e != 0)
            errx(EXIT_FAILURE, "pthread_create()");
        pthread_detach(thr);
    }
}
