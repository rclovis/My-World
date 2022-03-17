/*
** EPITECH PROJECT, 2022
** menu event
** File description:
** menu event
*/

#include "my_world.h"

void pause_menu_button_on_click(global *g, sfEvent *evt)
{
    menu_t *menu = get_curr_menu(g);
    if (menu == NULL) return;
    int x = evt->mouseButton.x;
    int y = evt->mouseButton.y;
    if (evt->type == 10 && g->curr_menu->data == M_PAUSE) {
        if (sfFloatRect_contains(&menu->buttons[0]->collision_box, x, y)) {
            play_music(g->click);
            g->curr_menu->data = 0;
        }
        if (sfFloatRect_contains(&menu->buttons[1]->collision_box, x, y)) {
            play_music(g->click);
            save_file(g->root, g->name);
        }
        if (sfFloatRect_contains(&menu->buttons[2]->collision_box, x, y)) {
            g->curr_menu->data = 0;
            play_music(g->click);
            g->complete2 = 1;
        }
    }
}

void main_menu_button_on_click(global *g, sfEvent *evt)
{
    menu_t *menu = get_curr_menu(g);
    if (menu == NULL) return;
    int x = evt->mouseButton.x;
    int y = evt->mouseButton.y;
    if (evt->type == 10 && g->curr_menu->data == M_MAIN) {
        if (sfFloatRect_contains(&menu->buttons[0]->collision_box, x, y)) {
            g->is_typing = 1;
            play_music(g->click);
            g->curr_menu = callstack_add(g->curr_menu, M_INPUT);
        }
        if (sfFloatRect_contains(&menu->buttons[1]->collision_box, x, y)) {
            g->is_typing = 1;
            play_music(g->click);
            g->curr_menu = callstack_add(g->curr_menu, M_INPUT);
        }
        if (sfFloatRect_contains(&menu->buttons[2]->collision_box, x, y)) {
            play_music(g->click);
            g->curr_menu = callstack_del(g->curr_menu);
        }
    }
}

int play_music (sfMusic *music)
{
        sfMusic_stop(music);
    sfMusic_play(music);
}

sfRenderStates *render_setup (sfTexture *texture)
{
    sfRenderStates *render = malloc(sizeof(sfRenderStates));
    render->texture = texture;
    render->transform = sfTransform_Identity;
    render->blendMode = sfBlendNone;
    render->shader = NULL;
    return render;
}
