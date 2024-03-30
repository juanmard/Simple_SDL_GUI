#include <stdio.h>
#include <stddef.h>

#include "graphic_utils.h"
#include "ssg.h"
#include "ssg_button.h"
#include "ssg_text.h"
#include "ssg_menu.h"
#include "ssg_menu_list.h"
#include "welcome.h"
#include "hall.h"

const int INIT_WIDTH = 640;
const int INIT_HEIGHT = 400;

int main(void)//int argc, char** argv)
{
    struct ssg_gui *my_gui = init_gui("SSG - Tests");

    if (set_font(my_gui, "img/font1.png") != 0)
    {
        fprintf(stderr, "LOG  : Closing GUI and returning with error code\n");
        close_gui(my_gui);
        return 1;
    }

    // MENU 1
    struct ssg_menu* menu1 = add_menu(my_gui->menu_list, "Welcome!");

    // MENU 2
    struct ssg_menu* menu2 = add_menu(my_gui->menu_list, "The Hall");

    // BUTTON 1
    struct ssg_button* button_1 = new_button_std(250, 50, "pink_button\
", 0xFF, 0x00, 0x55, "PINK BUTTON");

    // BUTTON 2
    struct ssg_button* button_2 =
        new_button_with_image(250, 120, "cian_button", 0x22, 0x44,
                              0xBB, "ANOTHER BUTTON",
                              "img/button_image.png", my_gui);
    if (!button_2)
    {
        fprintf(stderr, "LOG  : Closing GUI and returning with error code\n");
        free_button(button_1);
        close_gui(my_gui);
        return 1;
    }

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
    add_text_to_menu(menu1, text1);
    add_text_to_menu(menu2, text2);
    add_text_to_menu(menu2, text3);

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
                           &my_gui->menu_list->menu->name);

    enable_menu(my_gui->menu_list, menu1);
    print_background(my_gui->renderer);
    draw(my_gui);


    // for now, the debug text curr_menu_pointer goes separately
    event_loop(my_gui, curr_menu_pointer);

    free_debug_text(curr_menu_pointer);
    close_gui(my_gui);

    return 0;
}
