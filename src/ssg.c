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
    /*
    SDL_version my_version;
    SDL_GetVersion(&my_version);
    printf("%hhu.%hhu.%hhu\n", my_version.major, my_version.minor,
           my_version.patch);
    */
    unsigned int before = SDL_GetTicks();
    unsigned int now;
    char last_char = 'a';
    char curr_char;
    while(1)
    {
        SDL_WaitEventTimeout(&event,20);
        SDL_KeyboardEvent key_pressed = event.key;
        SDL_TextInputEvent input = event.text;
        SDL_TextEditingEvent edit = event.edit;
        switch(event.type)
        {
        /*
        case SDL_TEXTEDITING:
            printf("Edit: %s\n", edit.text);
            break;
        */
        case SDL_TEXTINPUT:
            now = SDL_GetTicks();
            curr_char = input.text[0];
            if (last_char != curr_char || now - before > 300)
            {
                write_to_focused_text_input(gui->menu_list->menu->texts, input);
                last_char = curr_char;
                before = now;
            }
            break;
        case SDL_KEYDOWN:
            now = SDL_GetTicks();
            curr_char = key_pressed.keysym.sym;
            if (curr_char == 8 && now - before > 75)
            {
                write_to_focused_text(gui->menu_list->menu->texts, key_pressed);
                last_char = curr_char;
                before = now;
            }
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
