/*
** EPITECH PROJECT, 2022
** B-MUL-200-MAR-2-1-myworld-erwan.gonzales
** File description:
** button
*/

#include "my_world.h"

menu_t * get_curr_menu(global *g)
{
    switch (g->curr_menu) {
    case 1:
        return g->main_menu;
    case 2:
        return g->pause_menu;
    case 3:
        return g->input_menu;
    default:
        return NULL;
    }
}

void render_menu(sfRenderWindow *win, menu_t *menu)
{
    for (int i = 0; menu->buttons[i] != NULL; i++) {
        sfRenderWindow_drawSprite(win, menu->buttons[i]->sprite, NULL);
        sfRenderWindow_drawText(win, menu->buttons[i]->text, NULL);
    }
}

button_t *button_init(const char *text, sfFont *font, sfTexture *texture)
{
    button_t *button = malloc(sizeof(button_t));

    button->sprite = sfSprite_create();
    button->text = sfText_create();
    button->texture = texture;
    button->rect = (sfIntRect) {0, 40, 400, 40};

    sfSprite_setTexture(button->sprite, button->texture, sfFalse);
    sfSprite_setTextureRect(button->sprite, button->rect);
    sfText_setFont(button->text, font);
    sfText_setString(button->text, text);

    return button;
}

menu_t *pause_menu_init(sfFont *font, sfTexture *button_texture)
{
    menu_t *menu = malloc(sizeof(menu_t));
    menu->buttons = malloc(sizeof(button_t *) * 5);

    menu->buttons[0] = button_init("RESUME", font, button_texture);
    menu->buttons[1] = button_init("LOAD", font, button_texture);
    menu->buttons[2] = button_init("SAVE", font, button_texture);
    menu->buttons[3] = button_init("QUIT", font, button_texture);
    menu->buttons[4] = NULL;

    sfSprite_setPosition(menu->buttons[0]->sprite, (sfVector2f) {200, 200});
    sfSprite_setPosition(menu->buttons[1]->sprite, (sfVector2f) {200, 250});
    sfSprite_setPosition(menu->buttons[2]->sprite, (sfVector2f) {200, 300});
    sfSprite_setPosition(menu->buttons[3]->sprite, (sfVector2f) {200, 350});

    sfText_setPosition(menu->buttons[0]->text, (sfVector2f) {350, 200});
    sfText_setPosition(menu->buttons[1]->text, (sfVector2f) {350, 250});
    sfText_setPosition(menu->buttons[2]->text, (sfVector2f) {350, 300});
    sfText_setPosition(menu->buttons[3]->text, (sfVector2f) {350, 350});

    return menu;
}

menu_t *main_menu_init(sfFont *font, sfTexture *button_texture)
{
    menu_t *menu = malloc(sizeof(menu_t));
    menu->buttons = malloc(sizeof(button_t *) * 4);

    menu->buttons[0] = button_init("CREATE", font, button_texture);
    menu->buttons[1] = button_init("LOAD", font, button_texture);
    menu->buttons[2]= button_init("QUIT", font, button_texture);
    menu->buttons[3] = NULL;

    sfSprite_setPosition(menu->buttons[0]->sprite, (sfVector2f) {200, 200});
    sfSprite_setPosition(menu->buttons[1]->sprite, (sfVector2f) {200, 250});
    sfSprite_setPosition(menu->buttons[2]->sprite, (sfVector2f) {200, 450});

    sfText_setPosition(menu->buttons[0]->text, (sfVector2f) {355, 200});
    sfText_setPosition(menu->buttons[1]->text, (sfVector2f) {370, 250});
    sfText_setPosition(menu->buttons[2]->text, (sfVector2f) {370, 450});

    return menu;
}

menu_t *input_menu_init(sfFont *font, sfTexture *button_texture)
{
    menu_t *menu = malloc(sizeof(menu_t));
    menu->buttons = malloc(sizeof(button_t *) * 3);

    menu->buttons[0] = button_init("ENTER SOME TEXT", font, button_texture);
    menu->buttons[1] = button_init("ENTER", font, button_texture);
    menu->buttons[2] = button_init("CANCEL", font, button_texture);
    menu->buttons[3] = NULL;

    menu->buttons[0]->rect.top = 0;
    sfSprite_setTextureRect(menu->buttons[0]->sprite, menu->buttons[0]->rect);

    sfSprite_setPosition(menu->buttons[0]->sprite, (sfVector2f) {200, 200});
    sfSprite_setPosition(menu->buttons[1]->sprite, (sfVector2f) {200, 400});
    sfSprite_setPosition(menu->buttons[2]->sprite, (sfVector2f) {200, 600});

    sfText_setPosition(menu->buttons[0]->text, (sfVector2f) {200, 200});
    sfText_setPosition(menu->buttons[1]->text, (sfVector2f) {200, 400});
    sfText_setPosition(menu->buttons[2]->text, (sfVector2f) {200, 600});

    return menu;
}

