#ifndef WELCOME_H
#define WELCOME_H

int check_pressed_buttons1(struct ssg_menu_list* menu_list,
                            struct ssg_button_list* list, int x, int y,
                            SDL_Renderer* renderer);
int check_pressed_texts1(struct ssg_menu_list* menu_list,
                            struct ssg_text_list* list, int x, int y,
                            SDL_Renderer* renderer);

#endif
