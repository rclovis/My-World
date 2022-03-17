/*
** EPITECH PROJECT, 2022
** create mesh
** File description:
** create mesh
*/

#include "../inc/my_world.h"

quad_list *create_mesh (int x, int y, sfVector3f pos, quad_list *root)
{
    quad_list *root_add = root, *ptr = NULL;
    sfTexture *t = sfTexture_createFromFile("assets/textures/textures.png", 0);
    float xx = 0, yy = 0;
    for (int i = 0;i < y;i++) {
        for (int j = 0;j < x;j++) {
            xx = j * 50 - ((x * 50) / 2) + pos.x;
            yy = i * 50 - ((y * 50) / 2) + pos.y;
            ptr = tri_one(xx, yy, pos.z, t);
            ptr->next = tri_two(xx, yy, pos.z, t);
            ptr->next->next = root_add;
            root_add = ptr;
        }
    }
    return root_add;
}

int append_vtx (sfVertexArray *array, sfVector2f tex, sfVector2f pos)
{
    sfVertex vtx = {pos, sfWhite, tex};
    sfVertexArray_append(array, vtx);
}

quad_list *tri_one (float x, float y, float z, sfTexture *texture)
{
    quad_list *e = malloc(sizeof(quad_list));
    e->n_texture = 0;
    e->display = 1;
    e->next = NULL;
    e->p1 = point_matrix (x, y + 50, z);
    e->p2 = point_matrix (x, y, z);
    e->p3 = point_matrix (x + 50, y, z);
    e->array = sfVertexArray_create();
    sfVertexArray_setPrimitiveType(e->array, sfTriangles);
    append_vtx(e->array, (sfVector2f) {0, 48}, (sfVector2f) {x, y + 50});
    append_vtx(e->array, (sfVector2f) {0, 0}, (sfVector2f) {x, y});
    append_vtx(e->array, (sfVector2f) {48, 0}, (sfVector2f) {x + 50, y});
    e->strip = sfVertexArray_create();
    sfVertexArray_setPrimitiveType(e->strip, sfLineStrip);
    append_vtx(e->strip, (sfVector2f) {0, 0}, (sfVector2f) {x, y + 50});
    append_vtx(e->strip, (sfVector2f) {0, 0}, (sfVector2f) {x, y});
    append_vtx(e->strip, (sfVector2f) {0, 0}, (sfVector2f) {x + 50, y});
    append_vtx(e->strip, (sfVector2f) {0, 0}, (sfVector2f) {x, y});
    e->render = render_setup(texture);
    return e;
}

quad_list *tri_two (float x, float y, float z, sfTexture *texture)
{
    quad_list *e = malloc(sizeof(quad_list));
    e->n_texture = 0;
    e->display = 1;
    e->next = NULL;
    e->p1 = point_matrix (x + 50, y, z);
    e->p2 = point_matrix (x + 50, y + 50, z);
    e->p3 = point_matrix (x, y + 50, z);
    e->array = sfVertexArray_create();
    sfVertexArray_setPrimitiveType(e->array, sfTriangles);
    append_vtx(e->array, (sfVector2f) {48, 0}, (sfVector2f) {x + 50, y});
    append_vtx(e->array, (sfVector2f) {48, 48}, (sfVector2f) {x + 50, y + 50});
    append_vtx(e->array, (sfVector2f) {0, 48}, (sfVector2f) {x, y + 50});
    e->strip = sfVertexArray_create();
    sfVertexArray_setPrimitiveType(e->strip, sfLineStrip);
    append_vtx(e->strip, (sfVector2f) {0, 0}, (sfVector2f) {x + 50, y});
    append_vtx(e->strip, (sfVector2f) {0, 0}, (sfVector2f) {x + 50, y + 50});
    append_vtx(e->strip, (sfVector2f) {0, 0}, (sfVector2f) {x, y + 50});
    append_vtx(e->strip, (sfVector2f) {0, 0}, (sfVector2f) {x + 50, y});
    e->render = render_setup(texture);
    return e;
}

float **point_matrix (float x, float y, float z)
{
    float **point = malloc(sizeof(float *) * 4);
    point[0] = malloc(sizeof(float));
    point[1] = malloc(sizeof(float));
    point[2] = malloc(sizeof(float));
    point[0][0] = x;
    point[1][0] = y;
    point[2][0] = z;
    point[3] = NULL;
    return point;
}
