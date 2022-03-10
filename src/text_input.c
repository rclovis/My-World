/*
** EPITECH PROJECT, 2022
** B-MUL-200-MAR-2-1-myworld-erwan.gonzales
** File description:
** text_input
*/

#include "my_world.h"

void activate_typing(global *g)
{
    if (g->will_type && !g->is_typing) {
        g->is_typing = 1;
        g->will_type = 0;
    }
}

void currently_typing(global *g, sfEvent *evt)
{
    if (evt->text.unicode == BACKSPACE) {
        (g->cursor > 0) ? (g->cursor--) : (0);
        g->input_buffer[g->cursor] = 0;
    }
    else if (evt->text.unicode == ENTER) {
        for (int l = 0; g->input_buffer[l] != 0; l++)
            printf("%c", g->input_buffer[l]);
        printf("\n");
        g->is_typing = 0;
        for (int j = 0; j < INPUT_BUFFER_SIZE; j++)
            g->input_buffer[j] = 0;
        g->cursor = 0;
    }
    else if (g->cursor < INPUT_BUFFER_SIZE - 1) {
        g->input_buffer[g->cursor] = evt->text.unicode;
        g->cursor++;
    }
    sfText_setUnicodeString(g->input_menu->buttons[0]->text, (const sfUint32 *) g->input_buffer);
}