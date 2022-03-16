/*
** EPITECH PROJECT, 2022
** B-MUL-200-MAR-2-1-myworld-erwan.gonzales
** File description:
** toolbar
*/

#include "my_world.h"

void render_toolbar(sfRenderWindow *win, toolbar_t *tb)
{
    //toolbar itself always first
    sfRenderWindow_drawSprite(win, tb->sprite, NULL);

    // toolbar icons
    sfRenderWindow_drawSprite(win, tb->icons[1], NULL);
    sfRenderWindow_drawSprite(win, tb->icons[2], NULL);
    sfRenderWindow_drawSprite(win, tb->icons[3], NULL);
    sfRenderWindow_drawSprite(win, tb->icons[4], NULL);
    sfRenderWindow_drawSprite(win, tb->icons[5], NULL);

    // render selection icon always after toolbar icons
    sfRenderWindow_drawSprite(win, tb->icons[0], NULL);
}

void move_toolbar_cursor(toolbar_t *tb, int new_mode)
{
    int diff = new_mode - tb->edit_mode;
    sfSprite_move(tb->icons[0], (sfVector2f) {0, 40 * diff});
}

void toggle_toolbar_visibility(toolbar_t *tb)
{
    // move toolbar
    sfSprite_move(tb->sprite, (sfVector2f) {50 * tb->view_toggle, 0});

    // move all icons
    for (int i = 0; tb->icons[i] != NULL; i++)
        sfSprite_move(tb->icons[i], (sfVector2f) {50 * tb->view_toggle, 0});
    for (int i = 0; i < tb->nb_icons; i++)
        tb->icons_rect[i] = sfSprite_getGlobalBounds(tb->icons[i]);

    // change next movement directiorn
    tb->view_toggle *= -1;
}

toolbar_t *setup_toolbar(void)
{
    toolbar_t *tb = malloc(sizeof(toolbar_t));

    // toolbar sprite
    tb->sprite = sfSprite_create();
    sfSprite_setTexture(tb->sprite,
        sfTexture_createFromFile("assets/gui/toolbar.png", NULL), sfTrue);
    sfSprite_setPosition(tb->sprite, (sfVector2f) {800, 100});
    sfSprite_setRotation(tb->sprite, 90.0);

    // tool selected. Also position on toolbar from top to bottom
    tb->edit_mode = 0;

    // toolar toggle var, alternate between 1 and -1
    tb->view_toggle = 1;

    // number of icons. Defined by YOU
    tb->nb_icons = 6;

    // generate all icons
    tb->icons = malloc(sizeof(sfSprite *) * (tb->nb_icons + 1));
    for (int i = 0; i < tb->nb_icons; i++)
        tb->icons[i] = sfSprite_create();
    tb->icons[tb->nb_icons] = NULL;

        //set textures
    sfSprite_setTexture(tb->icons[0],
        sfTexture_createFromFile("assets/gui/select_icon.png", NULL), sfTrue);
    sfSprite_setTexture(tb->icons[1],
        sfTexture_createFromFile("assets/gui/vertex_select.png", NULL), sfTrue);
    sfSprite_setTexture(tb->icons[2],
        sfTexture_createFromFile("assets/gui/edge_select.png", NULL), sfTrue);
    sfSprite_setTexture(tb->icons[3],
        sfTexture_createFromFile("assets/gui/face_select.png", NULL), sfTrue);
    sfSprite_setTexture(tb->icons[4],
        sfTexture_createFromFile("assets/gui/brush_icon.png", NULL), sfTrue);
    sfSprite_setTexture(tb->icons[5],
        sfTexture_createFromFile("assets/gui/ch_texture.png", NULL), sfTrue);

        // set positions
    sfSprite_setPosition(tb->icons[0], (sfVector2f) {757, 98});
    sfSprite_setPosition(tb->icons[1], (sfVector2f) {764, 106 + (40 * 0)});
    sfSprite_setPosition(tb->icons[2], (sfVector2f) {764, 106 + (40 * 1)});
    sfSprite_setPosition(tb->icons[3], (sfVector2f) {764, 106 + (40 * 2)});
    sfSprite_setPosition(tb->icons[4], (sfVector2f) {764, 106 + (40 * 3)});
    sfSprite_setPosition(tb->icons[5], (sfVector2f) {764, 106 + (40 * 4)});

    tb->icons_rect = malloc(sizeof(sfFloatRect) * (tb->nb_icons + 1));
    for (int i = 0; i < tb->nb_icons; i++)
        tb->icons_rect[i] = sfSprite_getGlobalBounds(tb->icons[i]);

    return tb;
}
