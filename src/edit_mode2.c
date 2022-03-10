/*
** EPITECH PROJECT, 2022
** edit_mode
** File description:
** edit_mode
*/

#include "../inc/my_world.h"

void raise_vertex (quad_list *root, sfVector2i m, int button, float strengh)
{
    sfVector2f *p = malloc(sizeof(sfVector2f) * 4);
    float height = (button == 1) ? strengh * -10 : strengh * 10;
    for (quad_list *ptr = root;ptr != NULL;ptr = ptr->next) {
        for (int i = 0;i < 3;i++)
            p[i] = sfVertexArray_getVertex(ptr->array, i)->position;
        if (approximation(p[0].x, m.x, 10) && approximation(p[0].y, m.y, 10))
            ptr->p1[2][0] += height;
        if (approximation(p[1].x, m.x, 10) && approximation(p[1].y, m.y, 10))
            ptr->p2[2][0] += height;
        if (approximation(p[2].x, m.x, 10) && approximation(p[2].y, m.y, 10))
            ptr->p3[2][0] += height;
    }
    free(p);
}

void raise_line (quad_list *root, sfVector2i m, int button, float strengh)
{
    sfVector2f *p = malloc(sizeof(sfVector2f) * 4);
    float a = 0, b = 0;
    int height = (button == 1) ? -10 : 10;
    for (quad_list *ptr = root;ptr != NULL;ptr = ptr->next) {
        for (int i = 0;i < 3;i++)
            p[i] = sfVertexArray_getVertex(ptr->array, i)->position;
        if (raise_line_bis(root, m, (sfVector2i) {button, strengh}, p) == 1)
            return;
    }
    free(p);
}

int raise_line_bis (quad_list *root, sfVector2i m, sfVector2i bs, sfVector2f *p)
{
    if (is_between(p[0], p[1], m)) {
        raise_vertex(root, (sfVector2i) {p[0].x, p[0].y}, bs.x, bs.y);
        raise_vertex(root, (sfVector2i) {p[1].x, p[1].y}, bs.x, bs.y);
        free(p);
        return 1;
    }
    if (is_between(p[1], p[2], m)) {
        raise_vertex(root, (sfVector2i) {p[1].x, p[1].y}, bs.x, bs.y);
        raise_vertex(root, (sfVector2i) {p[2].x, p[2].y}, bs.x, bs.y);
        free(p);
        return 1;
    }
    if (is_between(p[2], p[0], m)) {
        raise_vertex(root, (sfVector2i) {p[2].x, p[2].y}, bs.x, bs.y);
        raise_vertex(root, (sfVector2i) {p[0].x, p[0].y}, bs.x, bs.y);
        free(p);
        return 1;
    }
    return 0;
}

void raise_zone (quad_list *root, sfVector2i m, int button, float strengh)
{
    sfVector2f *p = malloc(sizeof(sfVector2f) * 4);
    int height = (button == 1) ? -1 : 1;
    float temp = 0;
    for (quad_list *ptr = root;ptr != NULL;ptr = ptr->next) {
        for (int i = 0;i < 3;i++)
            p[i] = sfVertexArray_getVertex(ptr->array, i)->position;
        temp = sqrt(pow(m.x - p[0].x, 2) + pow(m.y - p[0].y, 2));
        ptr->p1[2][0] +=  strengh * exp(-pow(temp / 10, 2) / 5);
        temp = sqrt(pow(m.x - p[1].x, 2) + pow(m.y - p[1].y, 2));
        ptr->p2[2][0] += strengh * exp(-pow(temp / 10, 2) / 5);
        temp = sqrt(pow(m.x - p[2].x, 2) + pow(m.y - p[2].y, 2));
        ptr->p3[2][0] += strengh * exp(-pow(temp / 10, 2) / 5);
    }
    free(p);
}

void raise_tile (quad_list *root, sfVector2i m, int button, float strengh)
{
    sfVector2f *p = malloc(sizeof(sfVector2f) * 4);
    float a = 0, b = 0;
    for (quad_list *ptr = root;ptr != NULL;ptr = ptr->next) {
        for (int i = 0;i < 3;i++)
            p[i] = sfVertexArray_getVertex(ptr->array, i)->position;
        if (is_in_triangle(m, p[0], p[1], p[2])) {
            raise_vertex(root, (sfVector2i) {p[0].x, p[0].y}, button, strengh);
            raise_vertex(root, (sfVector2i) {p[1].x, p[1].y}, button, strengh);
            raise_vertex(root, (sfVector2i) {p[2].x, p[2].y}, button, strengh);
            free(p);
            return;
        }
    }
    free(p);
}
