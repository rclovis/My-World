/*
** EPITECH PROJECT, 2021
** my_world
** File description:
** my_world
*/

#include "../inc/my_world.h"

int help_menu(int ac, char **av)
{
    if (!(ac == 2 && true_cmp(av[1], "-h") == 0))
        return 0;
    my_putstr("USAGE: ./my_world [-h | .]\n");
    my_putstr("\t-h\tdisplay this help menu\n");
    my_putstr("\t.\tsus ?\n");
    my_putstr("DESCRIPTION:\n");
    my_putstr("\tTerraformer simulator.\n");
    my_putstr("\tCreate your own world or import 3rd party 3d objects.\n");
    return 1;
}

int main (int argc, char **argv)
{
    if (help_menu(argc, argv))
        return 0;
    char *name;
    quad_list *root;
    sfMusic *music1 = sfMusic_createFromFile("assets/sounds/minecraft.ogg");
    sfMusic *music2 = sfMusic_createFromFile("assets/sounds/amogus.ogg");
    sfMusic_setLoop(music1, 1);
    sfMusic_setLoop(music2, 1);
    if (argc == 1)
        sfMusic_play(music1);
    else
        sfMusic_play(music2);
    sfRenderWindow *w = spinning_menu(argc - 1, &name, &root);
    my_world(w, name, root, argc);
    if (argc == 1)
        sfMusic_stop(music1);
    else
        sfMusic_stop(music2);
    return 1;
}


int my_world (sfRenderWindow *w, char *f, quad_list *r, int bool)
{
    if (w == 0) return 0;
    sfClock *clock = sfClock_create();
    sfEvent event;
    global *g = setup_global(f, r, bool - 1);
    g->curr_menu->data = 0;
    float time = 0, zoom = 1, x = 1,  z = 0.3;
    sfRenderWindow_setFramerateLimit(w, 60);
    while (sfRenderWindow_isOpen(w)) {
        display_fps(g->fps);
        time = sfClock_getElapsedTime(clock).microseconds / 2500000.0;
        place_circle(g->root, (sfVector2i) {-100, -100}, g->vertex);
        place_line(g->root, (sfVector2i) {-100, -100}, g->bevel);
        place_tile(g->root, (sfVector2i) {-100, -100}, g->tile);
        if (g->tb->edit_mode == 0)
            place_circle(g->root, sfMouse_getPositionRenderWindow(w), g->vertex);
        if (g->tb->edit_mode == 1)
            place_line(g->root, sfMouse_getPositionRenderWindow(w), g->bevel);
        if (g->tb->edit_mode == 2 || g->tb->edit_mode == 4)
            place_tile(g->root, sfMouse_getPositionRenderWindow(w), g->tile);
        while (sfRenderWindow_pollEvent(w, &event)) {
            (event.type == 0 || g->complete2 == 1) ? sfRenderWindow_close(w) : 0;
            menu_evt(g, &event, w);
            (g->curr_menu->data == 0) ? event_poll(event, g, g->root, w) : 0;
            if (event.type == sfEvtKeyReleased && event.key.code == 0) {
                g->curr_menu->data = (g->curr_menu->data == 0) ? 2 : 0;
            }
        }
        if (time > 0.01) {
            g->fps->frames++;
            sfRenderWindow_clear(w, sfBlue);
            g->state = 0;
            if (event.type == sfEvtKeyPressed || event.mouseWheel.type == 8) {
                g->state = 1;
                g->refresh = 1;
                zoom += event.mouseWheelScroll.delta * 0.1;
                event.mouseWheelScroll.delta = 0;
                (event.key.code == sfKeyUp) ? x -= 0.03 : 0;
                (event.key.code == sfKeyDown) ? x += 0.03 : 0;
                (event.key.code == sfKeyRight) ? z -= 0.03 : 0;
                (event.key.code == sfKeyLeft) ? z += 0.03 : 0;
            }
            (g->refresh == 1) ? update_mesh(g->root, zoom, x, z) : 0;
            (g->refresh == 1) ? g->root = push_swap(g->root) : 0;
            g->refresh = 0;

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
            sfClock_restart(clock);
        }

    }
    return 0;
}

void event_poll (sfEvent event, global *g, quad_list *root, sfRenderWindow *w)
{
    int buttons[5] = {76, 77, 78, 79, 80}, b = 0;
    int x = event.mouseButton.x, y = event.mouseButton.y;
    int is_clicking = (event.type == sfEvtMouseButtonReleased) ? 1 : 0;
    for (int i = 0;i < 5 && is_clicking == 1;i++) {
        if (sfFloatRect_contains(&g->tb->icons_rect[i + 1], x, y)) {
            move_toolbar_cursor(g->tb, i);
            g->tb->edit_mode = i;
            b++;
        }
    }
    if (b == 0)
        (clic_management(&event, root, w, g) == 1) ? g->refresh = 1 : 0;
    if (event.type != sfEvtKeyPressed) return;
    for (int i = 0;i < 5;i++) {
        if (event.key.code == buttons[i]) {
            move_toolbar_cursor(g->tb, i);
            g->tb->edit_mode = i;
        }
    }
    (event.key.code == 15) ? toggle_toolbar_visibility(g->tb) : 0;
}
