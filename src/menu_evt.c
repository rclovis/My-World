/*
** EPITECH PROJECT, 2022
** B-MUL-200-MAR-2-1-myworld-erwan.gonzales
** File description
** menu_evt
*/

#include "my_world.h"

void menu_evt(global *g, sfEvent *evt)
{
    menu_button_hover(g, evt);
    main_menu_button_on_click(g, evt);
    pause_menu_button_on_click(g, evt);
    input_menu_button_on_click(g, evt);
}

void menu_button_hover(global *g, sfEvent *evt)
{
    menu_t *menu;
    if ((menu =  get_curr_menu(g)) == NULL)
        return;
    int x = evt->mouseMove.x;
    int y = evt->mouseMove.y;
    if (evt->type != sfEvtMouseMoved)
        return;
    for (int i = 0; menu->buttons[i] != NULL; i++) {
        sfIntRect *rect = &menu->buttons[i]->rect;
        if (sfFloatRect_contains(&menu->buttons[i]->collision_box, x, y) &&
        !(i == 0 && g->curr_menu->data == M_INPUT)) {
            rect->top = 80;
            sfSprite_setTextureRect(menu->buttons[i]->sprite, *rect);
        }
        else if (!(i == 0 && g->curr_menu->data == M_INPUT)) {
            rect->top = 40;
            sfSprite_setTextureRect(menu->buttons[i]->sprite, *rect);
        }
    }
}

void input_menu_button_on_click(global *g, sfEvent *evt)
{
    menu_t *menu;
    if ((menu =  get_curr_menu(g)) == NULL)
        return;
    int x = evt->mouseButton.x;
    int y = evt->mouseButton.y;
    if (evt->type == 10 && g->curr_menu->data == M_INPUT) {
        if (sfFloatRect_contains(&menu->buttons[1]->collision_box, x, y)) {
            printf("Hello ENTER %d\n", g->curr_menu->data);
            g->curr_menu = callstack_del(g->curr_menu);
        }
        if (sfFloatRect_contains(&menu->buttons[2]->collision_box, x, y)) {
            printf("Hello CANCEL %d\n", g->curr_menu->data);
            g->curr_menu = callstack_del(g->curr_menu);
        }
    }
}

void pause_menu_button_on_click(global *g, sfEvent *evt)
{
    menu_t *menu;
    if ((menu =  get_curr_menu(g)) == NULL)
        return;
    int x = evt->mouseButton.x;
    int y = evt->mouseButton.y;
    if (evt->type == 10 && g->curr_menu->data == M_PAUSE) {
        if (sfFloatRect_contains(&menu->buttons[0]->collision_box, x, y)) {
            printf("Hello RESUME %d\n", g->curr_menu->data);
            g->curr_menu = callstack_del(g->curr_menu);
        }
        if (sfFloatRect_contains(&menu->buttons[1]->collision_box, x, y)) {
            printf("Hello LOAD %d\n", g->curr_menu->data);
            g->curr_menu = callstack_add(g->curr_menu, M_INPUT);
        }
        if (sfFloatRect_contains(&menu->buttons[2]->collision_box, x, y)) {
            printf("Hello SAVE %d\n", g->curr_menu->data);
            g->curr_menu = callstack_add(g->curr_menu, M_INPUT);
        }
        if (sfFloatRect_contains(&menu->buttons[3]->collision_box, x, y)) {
            printf("Hello QUIT %d\n", g->curr_menu->data);
            g->curr_menu = callstack_del(g->curr_menu);
        }
    }
}

void main_menu_button_on_click(global *g, sfEvent *evt)
{
    menu_t *menu;
    if ((menu =  get_curr_menu(g)) == NULL)
        return;
    int x = evt->mouseButton.x;
    int y = evt->mouseButton.y;
    if (evt->type == 10 && g->curr_menu->data == M_MAIN) {
        if (sfFloatRect_contains(&menu->buttons[0]->collision_box, x, y)) {
            printf("Hello CREATE %d\n", g->curr_menu->data);
            g->curr_menu = callstack_add(g->curr_menu, M_INPUT);
        }
        if (sfFloatRect_contains(&menu->buttons[1]->collision_box, x, y)) {
            printf("Hello LOAD %d\n", g->curr_menu->data);
            g->curr_menu = callstack_add(g->curr_menu, M_INPUT);
        }
        if (sfFloatRect_contains(&menu->buttons[2]->collision_box, x, y)) {
            printf("Hello QUIT %d\n", g->curr_menu->data);
            g->curr_menu = callstack_del(g->curr_menu);
        }
    }
}
