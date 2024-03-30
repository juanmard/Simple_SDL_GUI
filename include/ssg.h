#ifndef SSG_H
#define SSG_H

#include "ssg_gui.h"
#include "ssg_debug_text.h"

void draw(struct ssg_gui *gui);
void event_loop(struct ssg_gui *gui, struct ssg_debug_text *curr_menu_pointer);

#endif /* ! SSG_H */
