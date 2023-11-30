/*
** EPITECH PROJECT, 2022
** edit_mode
** File description:
** edit_mode
*/

#include "../inc/my_world.h"

void change_texture (quad_list *root, sfVector2i m, int button)
{
    sfVector2f *p = malloc(sizeof(sfVector2f) * 4);
    float a = 0, b = 0;
    (button != 1) ? button = -1 : 0;
    for (quad_list *ptr = root;ptr != NULL;ptr = ptr->next) {
        for (int i = 0;i < 3;i++)
            p[i] = sfVertexArray_getVertex(ptr->array, i)->position;
        if (is_in_triangle(m, p[0], p[1], p[2])) {
            ptr->n_texture += button;
            loop_button(&button, &ptr->n_texture);
            sfVertexArray_getVertex(ptr->array, 0)->texCoords.x += 48 * button;
            sfVertexArray_getVertex(ptr->array, 1)->texCoords.x += 48 * button;
            sfVertexArray_getVertex(ptr->array, 2)->texCoords.x += 48 * button;
            free(p);
            return;
        }
    }
    free(p);
}

void loop_button (int *button, int *n_texture)
{
    if (*n_texture == -1) {
        *n_texture = 25;
        *button = 25;
    }
    if (*n_texture == 26) {
        *n_texture = 0;
        *button = -25;
    }
}

int clic_management (sfEvent *event, quad_list *root,
sfRenderWindow *window, global_t *g)
{
    sfVector2f mouse_pos = sfRenderWindow_mapPixelToCoords(window, sfMouse_getPositionRenderWindow(window), NULL);
    sfVector2i m = {mouse_pos.x, mouse_pos.y};
    if (event->type != sfEvtMouseButtonReleased)
        return 0;
    if (g->tb->edit_mode == 0)
        raise_vertex(root, m, event->mouseButton.button, 1);
    if (g->tb->edit_mode == 1)
        raise_line(root, m, event->mouseButton.button, 1);
    if (g->tb->edit_mode == 2)
        raise_tile(root, m, event->mouseButton.button, 1);
    if (g->tb->edit_mode == 3)
        raise_zone(root, m, event->mouseButton.button, 10);
    if (g->tb->edit_mode == 4)
        change_texture(root, m, event->mouseButton.button);
    return 1;
}
