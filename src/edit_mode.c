/*
** EPITECH PROJECT, 2022
** edit_mode
** File description:
** edit_mode
*/

#include "../inc/my_world.h"

void raise_vertex (quad_list *root, sfVector2i m, int button)
{
    sfVector2f *p = malloc(sizeof(sfVector2f) * 4);
    int height = (button == 1) ? -10 : 10;
    for (quad_list *ptr = root;ptr != NULL;ptr = ptr->next) {
        for (int i = 0;i < 4;i++)
            p[i] = sfVertexArray_getVertex(ptr->array, i)->position;
        (approximation(p[0].x, m.x, 10) && approximation(p[0].y, m.y, 10)) ? ptr->p1[2][0] += height : 0;
        (approximation(p[1].x, m.x, 10) && approximation(p[1].y, m.y, 10)) ? ptr->p2[2][0] += height : 0;
        (approximation(p[2].x, m.x, 10) && approximation(p[2].y, m.y, 10)) ? ptr->p3[2][0] += height : 0;
        (approximation(p[3].x, m.x, 10) && approximation(p[3].y, m.y, 10)) ? ptr->p4[2][0] += height : 0;
    }
    free(p);
}

void raise_line (quad_list *root, sfVector2i m, int button)
{
    sfVector2f *p = malloc(sizeof(sfVector2f) * 4);
    float a = 0, b = 0;
    int height = (button == 1) ? -10 : 10;
    for (quad_list *ptr = root;ptr != NULL;ptr = ptr->next) {
        for (int i = 0;i < 4;i++)
            p[i] = sfVertexArray_getVertex(ptr->array, i)->position;

        if (is_between(p[0], p[1], m)) {
            raise_vertex(root, (sfVector2i) {p[0].x, p[0].y}, button);
            raise_vertex(root, (sfVector2i) {p[1].x, p[1].y}, button);
            free(p);
            return;
        }

        if (is_between(p[1], p[2], m)) {
            raise_vertex(root, (sfVector2i) {p[1].x, p[1].y}, button);
            raise_vertex(root, (sfVector2i) {p[2].x, p[2].y}, button);
            free(p);
            return;
        }

        if (is_between(p[2], p[3], m)) {
            raise_vertex(root, (sfVector2i) {p[2].x, p[2].y}, button);
            raise_vertex(root, (sfVector2i) {p[3].x, p[3].y}, button);
            free(p);
            return;
        }

        if (is_between(p[3], p[0], m)) {
            raise_vertex(root, (sfVector2i) {p[3].x, p[3].y}, button);
            raise_vertex(root, (sfVector2i) {p[0].x, p[0].y}, button);
            free(p);
            return;
        }
    }
    free(p);
}

void raise_tile (quad_list *root, sfVector2i m, int button)
{
    sfVector2f *p = malloc(sizeof(sfVector2f) * 4);
    float a = 0, b = 0;
    for (quad_list *ptr = root;ptr != NULL;ptr = ptr->next) {
        for (int i = 0;i < 4;i++)
            p[i] = sfVertexArray_getVertex(ptr->array, i)->position;
        if (is_in_triangle(m, p[3], p[0], p[1]) || is_in_triangle(m, p[1], p[2], p[3])) {
            raise_vertex(root, (sfVector2i) {p[0].x, p[0].y}, button);
            raise_vertex(root, (sfVector2i) {p[1].x, p[1].y}, button);
            raise_vertex(root, (sfVector2i) {p[2].x, p[2].y}, button);
            raise_vertex(root, (sfVector2i) {p[3].x, p[3].y}, button);
            free(p);
            return;
        }
    }
    free(p);
}

int clic_management (sfEvent *event, quad_list *root, sfRenderWindow *window, global *g)
{
    if (event->type != sfEvtMouseButtonReleased) {
        place_circle(root, (sfVector2i) {-100, -100}, g->vertex);
        place_line(root, (sfVector2i) {-100, -100}, g->bevel);
        place_tile(root, (sfVector2i) {-100, -100}, g->tile);
        if (g->edit_mode == 0)
            place_circle(root, sfMouse_getPositionRenderWindow(window), g->vertex);
        if (g->edit_mode == 1)
            place_line(root, sfMouse_getPositionRenderWindow(window), g->bevel);
        if (g->edit_mode == 2)
            place_tile(root, sfMouse_getPositionRenderWindow(window), g->tile);
        return 0;
    }
    if (g->edit_mode == 0)
        raise_vertex(root, sfMouse_getPositionRenderWindow(window), event->mouseButton.button);
    if (g->edit_mode == 1)
        raise_line(root, sfMouse_getPositionRenderWindow(window), event->mouseButton.button);
    if (g->edit_mode == 2)
        raise_tile(root, sfMouse_getPositionRenderWindow(window), event->mouseButton.button);
    event->type = 0;
    return 1;
}
