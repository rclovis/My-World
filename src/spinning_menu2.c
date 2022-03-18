/*
** EPITECH PROJECT, 2022
** B-MUL-200-MAR-2-1-myworld-erwan.gonzales
** File description:
** spinning_menu
*/

#include "my_world.h"

sfRenderWindow *win_init(void)
{
    sfVideoMode m = {800, 600, 32};
    sfRenderWindow *w = sfRenderWindow_create(m, "mw", sfResize | sfClose, 0);
    sfRenderWindow_setFramerateLimit(w, 60);
    return w;
}

void spinning_evt(sfRenderWindow *w, sfEvent *evt, global *g)
{
    while (sfRenderWindow_pollEvent(w, evt)) {
        menu_evt(g, evt, w);
        if (evt->type == sfEvtClosed || g->curr_menu == NULL )
            sfRenderWindow_close(w);
    }
}

quad_list *in_spin_time(sfRenderWindow *w, quad_list *r, global *g, sfClock *c)
{
    g->z += (g->v == 1) ? 0.05 : 0.01;
    sfRenderWindow_clear(w, sfBlue);
    update_mesh(r, g->zoom, g->x2, g->z);
    r = push_swap(r);
    for (quad_list *ptr = r;ptr != NULL; ptr = ptr->next) {
        if (ptr->display == 1) {
            sfRenderWindow_drawVertexArray(w, ptr->array, ptr->render);
            sfRenderWindow_drawVertexArray(w, ptr->strip, NULL);
        }
    }
    render_menu(w, g);
    sfRenderWindow_display(w);
    sfClock_restart(c);
    return r;
}
