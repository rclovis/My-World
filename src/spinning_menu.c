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

quad_list *spin_clock(sfClock *c, sfRenderWindow *w, quad_list *r, global *g)
{
    float time = sfClock_getElapsedTime(c).microseconds / 2500000.0;
    g->is_typing = (g->curr_menu != 0 && g->curr_menu->data == 3) ? 1 : 0;
    if (g->complete == 1 && g->id_menu == 0 && g->curr_menu->data == 3)
        g->curr_menu = callstack_add(g->curr_menu, M_COORDS);
    if (time > 0.00001) {
        r = in_spin_time(w, r, g, c);
    }
    return r;
}

quad_list *thing(global *g, quad_list *root)
{
    if (g->v == 1) {
        root = add_object(root, "assets/3d_objects/amogus",
        (sfVector3f) {-7, -7, -23});
        g->x2 = 1.57;
    } else {
        root = load_file(root, "save");
        g->x2 = 1;
    }
    return root;
}

sfRenderWindow *spinning_menu (int v, char **file, quad_list **to_send)
{
    sfRenderWindow *w = win_init();
    quad_list *root = NULL;
    global *g = setup_global(NULL, NULL, v);
    g->curr_menu->data = M_MAIN;
    root = thing(g, root);
    sfClock *clock = sfClock_create();
    sfEvent event;
    while (sfRenderWindow_isOpen(w)) {
        spinning_evt(w, &event, g);
        if (g->complete2 == 1 || g->complete == 1 && g->id_menu == 1) {
            char *name = malloc(sizeof(char) * 21);
            name[20] = '\0';
            for (int i = 0; i < 20; i++)
                name[i] = g->input_buffer[i];
            *file = my_strcat("assets/3d_objects/", name);
            if (g->v == 1) {
                *to_send = add_object(0, "assets/3d_objects/amogus", (sfVector3f) {-7, -7, -23});
                return (w);
            }
            if (g->complete2 == 1) {
                *to_send = create_mesh(g->x2, g->y, (sfVector3f) {0, 0, 0}, 0);
                return (w);
            }
            if (g->complete == 1 && g->id_menu == 1) {
                *to_send = load_file(NULL, *file);
                if (*to_send == NULL) {
                    g->complete = 0;
                    g->complete2 = 0;
                } else
                    return (w);
            }
        }
        root = spin_clock(clock, w, root, g);
    }
    free_quad_list(root);
    free(g);
    return 0;
}
