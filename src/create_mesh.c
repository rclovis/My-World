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
    sfTexture *texture = sfTexture_createFromFile("assets/textures/textures.png", NULL);
    float xx = 0, yy = 0;
    for (int i = 0;i < y;i++) {
        for (int j = 0;j < x;j++) {
            xx = j * 50 - ((x * 50) / 2) + pos.x;
            yy = i * 50 - ((y * 50) / 2) + pos.y;
            ptr = tri_one(xx, yy, pos.z, texture);
            ptr->next = tri_two(xx, yy, pos.z, texture);
            ptr->next->next = root_add;
            root_add = ptr;
        }
    }
    return root_add;
}

quad_list *tri_one (float x, float y, float z, sfTexture *texture)
{
    quad_list *elem = malloc(sizeof(quad_list));

    elem->n_texture = 0;
    elem->display = 1;
    elem->next = NULL;

    elem->p1 = point_matrix (x, y + 50, z);
    elem->p2 = point_matrix (x, y, z);
    elem->p3 = point_matrix (x + 50, y, z);

    elem->array = sfVertexArray_create();
    sfVertexArray_setPrimitiveType(elem->array, sfTriangles);

    sfVertexArray_append(elem->array, (sfVertex) {(sfVector2f) {x, y + 50}, sfWhite, (sfVector2f) {0, 48}});
    sfVertexArray_append(elem->array, (sfVertex) {(sfVector2f) {x, y}, sfWhite, (sfVector2f) {0, 0}});
    sfVertexArray_append(elem->array, (sfVertex) {(sfVector2f) {x + 50, y}, sfWhite, (sfVector2f) {48, 0}});

    elem->strip = sfVertexArray_create();
    sfVertexArray_setPrimitiveType(elem->strip, sfLineStrip);

    sfVertexArray_append(elem->strip, (sfVertex) {(sfVector2f) {x, y + 50}, sfWhite});
    sfVertexArray_append(elem->strip, (sfVertex) {(sfVector2f) {x, y}, sfWhite});
    sfVertexArray_append(elem->strip, (sfVertex) {(sfVector2f) {x + 50, y}, sfWhite});
    sfVertexArray_append(elem->strip, (sfVertex) {(sfVector2f) {x, y}, sfWhite});

    elem->render = malloc(sizeof(sfRenderStates));
    elem->render->texture = texture;
    elem->render->transform = sfTransform_Identity;
    elem->render->blendMode = sfBlendNone;
    elem->render->shader = NULL;
    return elem;
}

quad_list *tri_two (float x, float y, float z, sfTexture *texture)
{
    quad_list *elem = malloc(sizeof(quad_list));

    elem->n_texture = 0;
    elem->display = 1;
    elem->next = NULL;

    elem->p1 = point_matrix (x + 50, y, z);
    elem->p2 = point_matrix (x + 50, y + 50, z);
    elem->p3 = point_matrix (x, y + 50, z);

    elem->array = sfVertexArray_create();
    sfVertexArray_setPrimitiveType(elem->array, sfTriangles);

    sfVertexArray_append(elem->array, (sfVertex) {(sfVector2f) {x + 50, y}, sfWhite, (sfVector2f) {48, 0}});
    sfVertexArray_append(elem->array, (sfVertex) {(sfVector2f) {x + 50, y + 50}, sfWhite, (sfVector2f) {48, 48}});
    sfVertexArray_append(elem->array, (sfVertex) {(sfVector2f) {x, y + 50}, sfWhite, (sfVector2f) {0, 48}});

    elem->strip = sfVertexArray_create();
    sfVertexArray_setPrimitiveType(elem->strip, sfLineStrip);

    sfVertexArray_append(elem->strip, (sfVertex) {(sfVector2f) {x + 50, y}, sfWhite});
    sfVertexArray_append(elem->strip, (sfVertex) {(sfVector2f) {x + 50, y + 50}, sfWhite});
    sfVertexArray_append(elem->strip, (sfVertex) {(sfVector2f) {x, y + 50}, sfWhite});
    sfVertexArray_append(elem->strip, (sfVertex) {(sfVector2f) {x + 50, y}, sfWhite});

    elem->render = malloc(sizeof(sfRenderStates));
    elem->render->texture = texture;
    elem->render->transform = sfTransform_Identity;
    elem->render->blendMode = sfBlendNone;
    elem->render->shader = NULL;
    return elem;
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
