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

void event_poll (sfEvent event, global_t *g, quad_list *root, sfRenderWindow *w)
{
    int buttons[5] = {76, 77, 78, 79, 80}, b = 0;
    sfVector2f mouse_pos = sfRenderWindow_mapPixelToCoords(w, sfMouse_getPositionRenderWindow(w), NULL);
    int x = (int) mouse_pos.x;
    int y = (int) mouse_pos.y;
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
