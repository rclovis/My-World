/*
** EPITECH PROJECT, 2022
** B-MUL-200-MAR-2-1-myworld-erwan.gonzales
** File description:
** spinning_menu
*/

#include "my_world.h"

quad_list *spin_clock(sfClock *c, sfRenderWindow *w, quad_list *r, global_t *g)
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

quad_list *thing(global_t *g, quad_list *root)
{
    if (g->v == 1) {
        root = add_object(root, "assets/3d_objects/amogus",
        (sfVector3f) {-7, -7, -23});
        g->x2 = 1.57;
    } else {
        root = load_file(root, "saves/save");
        g->x2 = 1;
    }
    return root;
}

void aled (global_t *g, char **file, quad_list **to_send)
{
    char *name = malloc(sizeof(char) * 21), *path = "assets/3d_objects/amogus";
    name[20] = '\0';
    for (int i = 0; i < 20; name[i] = g->input_buffer[i], i++);
    *file = my_strcat("saves/", name);
    if (g->v == 1) {
        *to_send = add_object(0, path, (sfVector3f) {-7, -7, -23});
        return;
    }
    if (g->complete2 == 1) {
        *to_send = create_mesh(g->x, g->y, (sfVector3f) {0, 0, 0}, 0);
        return;
    }
    if (g->complete == 1 && g->id_menu == 1) {
        *to_send = load_file(NULL, *file);
        if (*to_send == NULL) {
            g->complete = 0;
            g->complete2 = 0;
        } else
            return;
    }
}

sfRenderWindow *spinning_menu (int v, char **file, quad_list **to_send)
{
    sfRenderWindow *w = win_init();
    quad_list *root = NULL;
    global_t *g = setup_global(NULL, NULL, v);
    g->curr_menu->data = M_MAIN;
    root = thing(g, root);
    sfClock *clock = sfClock_create();
    sfEvent event;
    while (sfRenderWindow_isOpen(w)) {
        spinning_evt(w, &event, g);
        if (g->complete2 == 1 || g->complete == 1 && g->id_menu == 1) {
            aled(g, file, to_send);
            return (w);
        }
        root = spin_clock(clock, w, root, g);
    }
    free_quad_list(root);
    free(g);
    return 0;
}
