#include <stdio.h>
#include <pthread.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <err.h>

#include "graphic_utils.h"
#include "ssg_button.h"
#include "ssg_menu.h"
#include "ssg_menu_list.h"

/* This is the .c file for the welcome menu, which has 3 buttons:
   - the pink one prints "Monday left me broken" and enables the
   second menu, described in the "hall.c" file
   - the orange one prints "this button is orange
   - the blue one prints "Tuesday I was through with hoping"
 */


/*
   check_pressed_buttons1()
   This function checks if there's a button in the ssg_button_list
   "list" that has been pressed
   - menu_list points to the ssg_menu_list where all the menus are
   "stored"
   - list is the ssg_button_list that we want to check if a button
   stored in it has been pressed or not
   - x and y are the coordinates where the Mouse Left Button has been
   pressed
   - renderer points to the SDL_Renderer where the current menu is
   being displayed
 */
void check_pressed_buttons1(struct ssg_menu_list* menu_list,
                            struct ssg_button_list* list, int x, int y,
                            SDL_Renderer* renderer)
{
    struct ssg_button* button;
    if ( (button =
          is_button_pressed_from_name(list, "pink_button", x, y)))
    {
        printf("Monday left me broken\n");

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
        enable_menu(menu_list, find_menu_name(menu_list,
                                              "(: second menu"));
    }
    if ((button =
         is_button_pressed_from_name(list, "cian_button", x, y)))
    {
        printf("Tuesday I was through with hoping\n");
        pthread_t thr;
        int e;
        e = pthread_create(&thr, NULL,
                           button_press_feedback,
                           (void*) button);
        if (e != 0)
            errx(EXIT_FAILURE, "pthread_create()");
        pthread_detach(thr);
    }
    if ((button =
         is_button_pressed_from_name(list, "orange_button", x, y)))
    {
        printf("this button is orange\n");
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
