/*
** EPITECH PROJECT, 2022
** B-MUL-200-MAR-2-1-myworld-erwan.gonzales
** File description:
** text_input
*/

#include "my_world.h"

void currently_typing(global_t *g, sfEvent *evt)
{
    if (evt->text.unicode == BACKSPACE) {
        (g->cursor > 0) ? (g->cursor--) : (0);
        g->input_buffer[g->cursor] = 0;
    } else if (evt->text.unicode == ENTER) {
        g->is_typing = 0;
        g->complete = 1;
    } else if (g->cursor < INPUT_BUFFER_SIZE - 1) {
        g->input_buffer[g->cursor] = evt->text.unicode;
        g->cursor++;
    }
    sfText_setUnicodeString(g->input_menu->buttons[0]->text,
        (const sfUint32 *) g->input_buffer);
}
