/*
** EPITECH PROJECT, 2022
** menu event
** File description:
** menu event
*/

#include "my_world.h"

void menu_evt(global *g, sfEvent *evt, sfRenderWindow *window)
{
    if (evt->type == sfEvtTextEntered && g->is_typing == 1)
        currently_typing(g, evt);

    menu_button_hover(g, evt);
    coords_menu_button_on_click(g, evt, window);
    main_menu_button_on_click(g, evt);
    pause_menu_button_on_click(g, evt);
    input_menu_button_on_click(g, evt);
}

void menu_button_hover(global *g, sfEvent *evt)
{
    menu_t *menu = get_curr_menu(g);
    if (menu == NULL) return;
    int x = evt->mouseMove.x;
    int y = evt->mouseMove.y;
    if (evt->type != sfEvtMouseMoved) return;
    for (int i = 0; menu->buttons[i] != NULL; i++) {
        sfIntRect *rect = &menu->buttons[i]->rect;
        if (sfFloatRect_contains(&menu->buttons[i]->collision_box, x, y) &&
        (!(i == 0 && g->curr_menu->data == 3) &&
        !(i < 2 && g->curr_menu->data == 4))) {
            rect->top = 80;
            (g->curr_menu->data == M_MAIN) ? g->id_menu = i : 0;
            sfSprite_setTextureRect(menu->buttons[i]->sprite, *rect);
        } else if (!(i == 0 && g->curr_menu->data == 3) &&
        !(i < 2 && g->curr_menu->data == 4)) {
            rect->top = 40;
            sfSprite_setTextureRect(menu->buttons[i]->sprite, *rect);
        }
    }
}

void input_menu_button_on_click(global *g, sfEvent *evt)
{
    menu_t *menu = get_curr_menu(g);
    if (menu == NULL) return;
    int x = evt->mouseButton.x;
    int y = evt->mouseButton.y;
    if (evt->type == 10 && g->curr_menu->data == M_INPUT) {
        if (sfFloatRect_contains(&menu->buttons[1]->collision_box, x, y)) {
            g->is_typing = 0;
            play_music(g->click);
            g->complete = 1;
        }
        if (sfFloatRect_contains(&menu->buttons[2]->collision_box, x, y)) {
            g->is_typing = 0;
            play_music(g->click);
            g->curr_menu = callstack_del(g->curr_menu);
        }
    }
}

int truc (menu_t *menu, sfEvent *evt, sfVector2i v, global *g)
{
    if (g->curr_menu->data == M_COORDS && evt->type == 10) {
        if (sfFloatRect_contains(&menu->buttons[2]->collision_box, v.x, v.y)) {
            play_music(g->click);
            g->complete2 = 1;
        }
        if (sfFloatRect_contains(&menu->buttons[3]->collision_box, v.x, v.y)) {
            g->curr_menu = callstack_del(g->curr_menu);
            play_music(g->click);
            g->complete = 0;
        }
    }
    button_t *b1 = menu->buttons[0];
    button_t *b2 = menu->buttons[1];
    if (g->curr_menu->data == M_COORDS) {
        sfText_setString(b1->text, my_strcat("X SIZE ", int_to_char(g->x)));
        sfText_setString(b2->text, my_strcat("Y SIZE ", int_to_char(g->y)));
    }
}

void coords_menu_button_on_click(global *g, sfEvent *evt, sfRenderWindow* w)
{
    menu_t *menu = get_curr_menu(g);
    if (menu == NULL) return;
    int x = sfMouse_getPositionRenderWindow(w).x;
    int y = sfMouse_getPositionRenderWindow(w).y;
    int tmp = 0;
    if (g->curr_menu->data == M_COORDS && evt->mouseWheel.type == 8) {
        if (sfFloatRect_contains(&menu->buttons[0]->collision_box, x, y)) {
            tmp = g->x + evt->mouseWheelScroll.delta;
            (tmp >= 1 && tmp <= 200) ? g->x = tmp : 0;
            evt->mouseWheelScroll.delta = 0;
        }
        if (sfFloatRect_contains(&menu->buttons[1]->collision_box, x, y)) {
            tmp = g->y + evt->mouseWheelScroll.delta;
            (tmp >= 1 && tmp <= 200) ? g->y = tmp : 0;
            evt->mouseWheelScroll.delta = 0;
        }
    }
    truc(menu, evt, (sfVector2i) {x, y}, g);
}
