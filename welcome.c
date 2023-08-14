#include <stdio.h>
#include <pthread.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <err.h>

#include "ssg_button.h"
#include "ssg_menu.h"

/* This is the .c file for the welcome menu, which has 3 buttons:
   the pink one prints "Monday left me broken", the orange one
   prints another string, and the third one prints something else
 */

void check_pressed_buttons(struct ssg_button_list* list, int x, int y)
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
        printf("Wednesday my ...... are broken\n");
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
