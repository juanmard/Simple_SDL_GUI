#include "ssg.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "graphic_utils.h"

void draw(struct ssg_gui *gui)
{
    SDL_RenderPresent(gui->renderer);
}

void event_loop(struct ssg_gui *gui, struct ssg_debug_text* curr_menu_pointer)
{
    SDL_Event event;
    event.type = SDL_WINDOWEVENT;
    int mbl_pushed = 0;
    while(1)
    {
        SDL_WaitEventTimeout(&event,20);
        int i = event.key.keysym.sym;
        switch(event.type)
        {
        case SDL_KEYDOWN:
            write_to_texts(gui->menu_list->menu, i);
            break;
        case SDL_QUIT:
            return;
        case SDL_WINDOWEVENT:
            if(event.window.event == SDL_WINDOWEVENT_RESIZED)
            {
                print_menu(gui->renderer, gui->menu_list->menu, gui->font);
                // the "multiple-menus-being-displayed-at-the-same-
                // time" problem's cause  might be here
                //print_menu(renderer, sub_menu_list->menu, font);
                update_menu_name_pointer(curr_menu_pointer, gui->menu_list);
                print_ssg_debug_text(gui->renderer, curr_menu_pointer,
                        gui->font);
                draw(gui);
            }
            break;
        case SDL_MOUSEBUTTONDOWN:
            if(event.button.button == SDL_BUTTON_LEFT)
            {
                if(mbl_pushed)
                    break;
                mbl_pushed = 1;
                gui->menu_list->menu->texts->text = NULL;
                int chbt = check_button(gui->menu_list, gui->menu_list->menu,
                             event.button.x, event.button.y,
                             gui->renderer);
                if (chbt != 0)
                {
                    fprintf(stderr, "LOG  : breaking after check_button\n");
                    return;
                }

                int chtx = check_text(gui->menu_list, gui->menu_list->menu,
                        event.button.x, event.button.y,
                        gui->renderer);
                if (chtx != 0)
                {
                    fprintf(stderr, "LOG  : breaking after text_button\n");
                    return;
                }
            }
            break;
        case SDL_MOUSEBUTTONUP:
            if(event.button.button == SDL_BUTTON_LEFT)
                mbl_pushed = 0;
        default:
            break;
        }
        print_background(gui->renderer);
        print_menu(gui->renderer, gui->menu_list->menu, gui->font);
        //print_menu(renderer, sub_menu_list->menu, font);
        update_menu_name_pointer(curr_menu_pointer, gui->menu_list);
        print_ssg_debug_text(gui->renderer, curr_menu_pointer, gui->font);
        draw(gui);
    }
}
