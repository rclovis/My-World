/*
** EPITECH PROJECT, 2022
** button
** File description:
** button
*/

#include "my_world.h"

menu_t *input_menu_init(sfFont *font, sfTexture *button_texture)
{
    menu_t *menu = malloc(sizeof(menu_t));
    menu->buttons = malloc(sizeof(button_t *) * 4);
    menu->buttons[0] = button_init("ENTER SOME TEXT", font, button_texture);
    menu->buttons[1] = button_init("ENTER", font, button_texture);
    menu->buttons[2] = button_init("CANCEL", font, button_texture);
    menu->buttons[3] = NULL;
    menu->buttons[0]->rect.top = 0;
    sfSprite_setTextureRect(menu->buttons[0]->sprite, menu->buttons[0]->rect);
    sfSprite_setPosition(menu->buttons[0]->sprite, (sfVector2f) {200, 200});
    sfSprite_setPosition(menu->buttons[1]->sprite, (sfVector2f) {200, 350});
    sfSprite_setPosition(menu->buttons[2]->sprite, (sfVector2f) {200, 400});
    sfText_setPosition(menu->buttons[0]->text, (sfVector2f) {205, 200});
    sfText_setPosition(menu->buttons[1]->text, (sfVector2f) {205, 350});
    sfText_setPosition(menu->buttons[2]->text, (sfVector2f) {205, 400});
    for (int i = 0; menu->buttons[i] != NULL; i++) {
        menu->buttons[i]->collision_box = sfSprite_getGlobalBounds(
        menu->buttons[i]->sprite);
    }
    return menu;
}

menu_t *coords_menu_init(sfFont *font, sfTexture *button_texture)
{
    menu_t *menu = malloc(sizeof(menu_t));
    menu->buttons = malloc(sizeof(button_t *) * 5);
    menu->buttons[0] = button_init("X SIZE", font, button_texture);
    menu->buttons[1] = button_init("Y SIZE", font, button_texture);
    menu->buttons[2] = button_init("ENTER", font, button_texture);
    menu->buttons[3] = button_init("CANCEL", font, button_texture);
    menu->buttons[4] = NULL;
    menu->buttons[0]->rect.top = 0;
    sfSprite_setTextureRect(menu->buttons[0]->sprite, menu->buttons[0]->rect);
    menu->buttons[1]->rect.top = 0;
    sfSprite_setTextureRect(menu->buttons[1]->sprite, menu->buttons[1]->rect);
    sfSprite_setPosition(menu->buttons[0]->sprite, (sfVector2f) {200, 200});
    sfSprite_setPosition(menu->buttons[1]->sprite, (sfVector2f) {200, 250});
    sfSprite_setPosition(menu->buttons[2]->sprite, (sfVector2f) {200, 350});
    sfSprite_setPosition(menu->buttons[3]->sprite, (sfVector2f) {200, 400});
    sfText_setPosition(menu->buttons[0]->text, (sfVector2f) {205, 200});
    sfText_setPosition(menu->buttons[1]->text, (sfVector2f) {205, 250});
    sfText_setPosition(menu->buttons[2]->text, (sfVector2f) {205, 350});
    sfText_setPosition(menu->buttons[3]->text, (sfVector2f) {205, 400});
    for (int i = 0; menu->buttons[i] != NULL; i++)
        menu->buttons[i]->collision_box = sfSprite_getGlobalBounds(
        menu->buttons[i]->sprite);
    return menu;
}
