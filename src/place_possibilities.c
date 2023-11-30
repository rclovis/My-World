/*
** EPITECH PROJECT, 2022
** place
** File description:
** place
*/

#include "../inc/my_world.h"

void place_circle (quad_list *root, sfVector2i m, sfCircleShape *c)
{
    sfVector2f p1, p2, p3, p4;
    sfVector2f *p = calloc(sizeof(sfVector2f), 4);
    for (quad_list *ptr = root;ptr != NULL;ptr = ptr->next) {
        if (ptr->display == 0) continue;
        if (sfVertexArray_getVertexCount(ptr->array) != 3) continue;
        for (int i = 0;i < 3;i++)
            p[i] = sfVertexArray_getVertex(ptr->array, i)->position;
        if (approximation(p[0].x, m.x, 10) && approximation(p[0].y, m.y, 10)) {
            sfCircleShape_setPosition(c, (sfVector2f) {p[0].x, p[0].y});
            return free(p);
        }
        if (approximation(p[1].x, m.x, 10) && approximation(p[1].y, m.y, 10)) {
            sfCircleShape_setPosition(c, (sfVector2f) {p[1].x, p[1].y});
            return free(p);
        }
        if (approximation(p[2].x, m.x, 10) && approximation(p[2].y, m.y, 10)) {
            sfCircleShape_setPosition(c, (sfVector2f) {p[2].x, p[2].y});
            return free(p);
        }
    }
    sfCircleShape_setPosition(c, (sfVector2f) {-100, -100});
    free(p);
}

void place_line (quad_list *root, sfVector2i m, sfVertexArray *bevel)
{
    sfVector2f *p = calloc(sizeof(sfVector2f), 4);
    for (quad_list *ptr = root;ptr != NULL;ptr = ptr->next) {
        if (sfVertexArray_getVertexCount(ptr->array) != 3) continue;
        for (int i = 0;i < 3;i++)
            p[i] = sfVertexArray_getVertex(ptr->array, i)->position;
        if (is_between(p[0], p[1], m)) {
            sfVertexArray_getVertex(bevel, 0)->position = p[0];
            sfVertexArray_getVertex(bevel, 1)->position = p[1];
            return free(p);
        }
        if (is_between(p[1], p[2], m)) {
            sfVertexArray_getVertex(bevel, 0)->position = p[1];
            sfVertexArray_getVertex(bevel, 1)->position = p[2];
            return free(p);
        }
        if (is_between(p[2], p[0], m)) {
            sfVertexArray_getVertex(bevel, 0)->position = p[2];
            sfVertexArray_getVertex(bevel, 1)->position = p[0];
            return free(p);
        }
    }
    sfVertexArray_getVertex(bevel, 0)->position = (sfVector2f) {-100, -100};
    sfVertexArray_getVertex(bevel, 1)->position = (sfVector2f) {-100, -100};
    free(p);
}

void place_tile (quad_list *root, sfVector2i m, sfVertexArray *tile)
{
    sfVector2f *p = calloc(sizeof(sfVector2f), 4);
    float a = 0, b = 0;
    for (quad_list *ptr = root;ptr != NULL;ptr = ptr->next) {
        if (sfVertexArray_getVertexCount(ptr->array) != 3) continue;
        for (int i = 0;i < 3;i++)
            p[i] = sfVertexArray_getVertex(ptr->array, i)->position;

        if (is_in_triangle(m, p[0], p[1], p[2])) {
            sfVertexArray_getVertex(tile, 0)->position = p[0];
            sfVertexArray_getVertex(tile, 1)->position = p[1];
            sfVertexArray_getVertex(tile, 2)->position = p[2];
            sfVertexArray_getVertex(tile, 3)->position = p[0];
            free(p);
            return;
        }
    }
    sfVertexArray_getVertex(tile, 0)->position = (sfVector2f) {-100, -100};
    sfVertexArray_getVertex(tile, 1)->position = (sfVector2f) {-100, -100};
    sfVertexArray_getVertex(tile, 2)->position = (sfVector2f) {-100, -100};
    sfVertexArray_getVertex(tile, 3)->position = (sfVector2f) {-100, -100};
    free(p);
}

int is_in_triangle (sfVector2i pt, sfVector2f v1, sfVector2f v2, sfVector2f v3)
{
    float p1 = (pt.x - v2.x) * (v1.y - v2.y) - (v1.x - v2.x) * (pt.y - v2.y);
    float p2 = (pt.x - v3.x) * (v2.y - v3.y) - (v2.x - v3.x) * (pt.y - v3.y);
    float p3 = (pt.x - v1.x) * (v3.y - v1.y) - (v3.x - v1.x) * (pt.y - v1.y);
    if ((p1 < 0) || (p2 < 0) || (p3 < 0)) {
        if ((p1 > 0) || (p2 > 0) || (p3 > 0))
            return 0;
    }
    return 1;
}

int is_between (sfVector2f p1, sfVector2f p2, sfVector2i m)
{
    sfVector2f v1 = {p2.x - p1.x, p2.y - p1.y};
    sfVector2f v2 = {m.x - p1.x, m.y - p1.y};
    float tmp1 = v1.x * v2.y - v1.y * v2.x;
    float tmp2 = 5 * sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
    float tmp3 = v1.x * v2.x + v1.y * v2.y;
    if (approximation(tmp1, 0, tmp2) == 0)
        return (0);
    if (0 < tmp3 && tmp3 < v1.x * v1.x + v1.y * v1.y)
        return (1);
    return (0);
}
