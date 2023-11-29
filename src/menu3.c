/*
** EPITECH PROJECT, 2022
** menu
** File description:
** menu
*/

#include "../inc/my_world.h"

global_t *aled2 (global_t *g, sfClock *clock, sfEvent *event, sfRenderWindow *w)
{
    display_fps(g->fps);
    place_circle(g->root, (sfVector2i) {-100, -100}, g->vertex);
    place_line(g->root, (sfVector2i) {-100, -100}, g->bevel);
    place_tile(g->root, (sfVector2i) {-100, -100}, g->tile);
    if (g->tb->edit_mode == 0)
        place_circle(g->root, sfMouse_getPositionRenderWindow(w), g->vertex);
    if (g->tb->edit_mode == 1)
        place_line(g->root, sfMouse_getPositionRenderWindow(w), g->bevel);
    if (g->tb->edit_mode == 2 || g->tb->edit_mode == 4)
        place_tile(g->root, sfMouse_getPositionRenderWindow(w), g->tile);
    while (sfRenderWindow_pollEvent(w, event)) {
        (event->type == 0 || g->complete2 == 1) ? sfRenderWindow_close(w) : 0;
        menu_evt(g, event, w);
        (g->curr_menu->data == 0) ? event_poll(*event, g, g->root, w) : 0;
        if (event->type == sfEvtKeyReleased && event->key.code == 0)
            g->curr_menu->data = (g->curr_menu->data == 0) ? 2 : 0;
    }
    return g;
}

void aled3 (global_t *g, sfRenderWindow *w)
{
    for (quad_list *ptr = g->root;ptr != NULL; ptr = ptr->next) {
        if (ptr->display == 1) {
            if (g->state == 0)
                sfRenderWindow_drawVertexArray(w, ptr->array, ptr->render);
            sfRenderWindow_drawVertexArray(w, ptr->strip, NULL);
        }
    }
    sfRenderWindow_drawText(w, g->fps->text, NULL);
    sfRenderWindow_drawVertexArray(w, g->bevel, NULL);
    sfRenderWindow_drawVertexArray(w, g->tile, NULL);
    sfRenderWindow_drawCircleShape(w, g->vertex, NULL);
    render_toolbar(w, g->tb);
    render_menu(w, g);
    sfRenderWindow_display(w);
}

global_t *aled4 (global_t *g, float *zoom, float *z, sfEvent *event)
{
    g->fps->frames++;
    g->state = 0;
    if (event->type == sfEvtKeyPressed || event->mouseWheel.type == 8) {
        g->state = 1;
        g->refresh = 1;
        *zoom += event->mouseWheelScroll.delta * 0.1;
        event->mouseWheelScroll.delta = 0;
        (event->key.code == sfKeyUp) ? g->x2 -= 0.03 : 0;
        (event->key.code == sfKeyDown) ? g->x2 += 0.03 : 0;
        (event->key.code == sfKeyRight) ? *z = *z - 0.03 : 0;
        (event->key.code == sfKeyLeft) ? *z = *z + 0.03 : 0;
    }
    return g;
}

int my_world (sfRenderWindow *w, char *f, quad_list *r, int bool)
{
    if (w == 0) return 0;
    sfClock *clock = sfClock_create();
    sfEvent event;
    global_t *g = setup_global(f, r, bool - 1);
    float time = 0, zoom = 1, z = 0.3;
    sfRenderWindow_setFramerateLimit(w, 60);
    while (sfRenderWindow_isOpen(w)) {
        time = sfClock_getElapsedTime(clock).microseconds / 2500000.0;
        aled2(g, clock, &event, w);
        if (time > 0.01) {
            sfRenderWindow_clear(w, sfBlue);
            g = aled4(g, &zoom, &z, &event);
            (g->refresh == 1) ? update_mesh(g->root, zoom, g->x2, z) : 0;
            (g->refresh == 1) ? g->root = push_swap(g->root) : 0;
            g->refresh = 0;
            aled3(g, w);
            sfClock_restart(clock);
        }
    }
    return 0;
}
