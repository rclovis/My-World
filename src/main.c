/*
** EPITECH PROJECT, 2021
** likedvis
** File description:
** likedvis
*/

#include "../inc/likedvis.h"

int main (int argc, char **argv)
{
    return likedvis(argc, argv);
}

int likedvis (int argc, char **argv)
{
    sfVideoMode mode = {800, 600, 32};
    sfRenderWindow *window = sfRenderWindow_create(mode, "my_world", sfResize | sfClose, NULL);
    sfTexture *yes = sfTexture_createFromFile("sand.png", NULL);
    quad_list *root = create_mesh(10, 10, yes);
    sfClock *clock = sfClock_create();
    sfEvent event;

    global *g = malloc(sizeof(global));
    g->edit_mode = 0;
    g->apply_mode = 0;
    g->vertex = sfCircleShape_create();
    sfCircleShape_setRadius(g->vertex, 5);
    sfCircleShape_setFillColor(g->vertex, sfBlack);
    sfCircleShape_setOrigin(g->vertex, (sfVector2f) {5, 5});

    g->bevel = sfVertexArray_create();
    sfVertexArray_setPrimitiveType(g->bevel, sfLines);
    sfVertexArray_append(g->bevel, (sfVertex) {(sfVector2f) {-100, -100}, sfBlack});
    sfVertexArray_append(g->bevel, (sfVertex) {(sfVector2f) {-100, -101}, sfBlack});

    g->tile = sfVertexArray_create();
    sfVertexArray_setPrimitiveType(g->tile, sfLinesStrip);
    sfVertexArray_append(g->tile, (sfVertex) {(sfVector2f) {-100, -100}, sfBlack});
    sfVertexArray_append(g->tile, (sfVertex) {(sfVector2f) {-100, -100}, sfBlack});
    sfVertexArray_append(g->tile, (sfVertex) {(sfVector2f) {-100, -100}, sfBlack});
    sfVertexArray_append(g->tile, (sfVertex) {(sfVector2f) {-100, -100}, sfBlack});
    sfVertexArray_append(g->tile, (sfVertex) {(sfVector2f) {-100, -100}, sfBlack});

    float time = 0, zoom = 1, x = 1,  z = 0.3;

    sfRenderWindow_setFramerateLimit(window, 60);
    while (sfRenderWindow_isOpen(window)) {
        time = sfClock_getElapsedTime(clock).microseconds / 2500000.0;
        (x >= 6.28 || x <= -6.28) ? x = 0 : 0;
        (z >= 6.28 || z <= -6.28) ? z = 0 : 0;
        clic_management(&event, root, window, g);
        if (time > 0.01) {
            if (event.type == sfEvtKeyPressed) {
                (event.key.code == sfKeyUp) ? x -= 0.03 : 0;
                (event.key.code == sfKeyDown) ? x += 0.03 : 0;
                (event.key.code == sfKeyRight) ? z -= 0.03 : 0;
                (event.key.code == sfKeyLeft) ? z += 0.03 : 0;
            }
            (event.key.code == sfKeyNumpad0) ? g->edit_mode = 0 : 0;
            (event.key.code == sfKeyNumpad1) ? g->edit_mode = 1 : 0;
            (event.key.code == sfKeyNumpad2) ? g->edit_mode = 2 : 0;
            zoom += event.mouseWheelScroll.delta * 0.1;
            event.mouseWheelScroll.delta = 0;
            update_mesh(root, zoom, x, z);
            root = push_swap(root);
            while (sfRenderWindow_pollEvent(window, &event))
                (event.type == sfEvtClosed) ? sfRenderWindow_close(window) : 0;
            sfRenderWindow_clear(window, sfBlue);
            for (quad_list *ptr = root;ptr != NULL; ptr = ptr->next) {
                sfRenderWindow_drawVertexArray(window, ptr->array, ptr->render);
                sfRenderWindow_drawVertexArray(window, ptr->strip, NULL);
            }
            sfRenderWindow_drawVertexArray(window, g->bevel, NULL);
            sfRenderWindow_drawVertexArray(window, g->tile, NULL);
            sfRenderWindow_drawCircleShape(window, g->vertex, NULL);
            sfClock_restart(clock);
        }

        sfRenderWindow_display(window);
    }
    return 0;
}

quad_list *create_mesh (int x, int y, sfTexture *texture)
{
    quad_list *root = NULL, *ptr = NULL;
    for (int i = 0;i < y;i++) {
        for (int j = 0;j < x;j++) {
            ptr = new_elem(j * 50 - ((x * 50) / 2), i * 50 - ((y * 50) / 2), texture);
            ptr->next = root;
            root = ptr;
        }
    }
    return root;
}

quad_list *new_elem (float x, float y, sfTexture *texture)
{
    quad_list *elem = malloc(sizeof(quad_list));
    elem->array = sfVertexArray_create();
    sfVertexArray_setPrimitiveType(elem->array, sfQuads);
    elem->n_texture = 0;

    elem->nbr = 0;
    elem->p1 = malloc(sizeof(float *) * 4);
    elem->p2 = malloc(sizeof(float *) * 4);
    elem->p3 = malloc(sizeof(float *) * 4);
    elem->p4 = malloc(sizeof(float *) * 4);

    elem->p1[0] = malloc(sizeof(float));
    elem->p1[1] = malloc(sizeof(float));
    elem->p1[2] = malloc(sizeof(float));
    elem->p1[0][0] = x;
    elem->p1[1][0] = y;
    elem->p1[2][0] = 0;
    elem->p1[3] = NULL;

    elem->p2[0] = malloc(sizeof(float));
    elem->p2[1] = malloc(sizeof(float));
    elem->p2[2] = malloc(sizeof(float));
    elem->p2[0][0] = x + 50;
    elem->p2[1][0] = y;
    elem->p2[2][0] = 0;
    elem->p2[3] = NULL;

    elem->p3[0] = malloc(sizeof(float));
    elem->p3[1] = malloc(sizeof(float));
    elem->p3[2] = malloc(sizeof(float));
    elem->p3[0][0] = x + 50;
    elem->p3[1][0] = y + 50;
    elem->p3[2][0] = 0;
    elem->p3[3] = NULL;

    elem->p4[0] = malloc(sizeof(float));
    elem->p4[1] = malloc(sizeof(float));
    elem->p4[2] = malloc(sizeof(float));
    elem->p4[0][0] = x;
    elem->p4[1][0] = y + 50;
    elem->p4[2][0] = 0;
    elem->p4[3] = NULL;

    sfVertexArray_append(elem->array, (sfVertex) {(sfVector2f) {x, y}, sfWhite, (sfVector2f) {0, 0}});
    sfVertexArray_append(elem->array, (sfVertex) {(sfVector2f) {x + 50, y}, sfWhite, (sfVector2f) {0, 160}});
    sfVertexArray_append(elem->array, (sfVertex) {(sfVector2f) {x + 50, y + 50}, sfWhite, (sfVector2f) {160, 160}});
    sfVertexArray_append(elem->array, (sfVertex) {(sfVector2f) {x, y + 50}, sfWhite, (sfVector2f) {160, 0}});

    elem->strip = sfVertexArray_create();
    sfVertexArray_setPrimitiveType(elem->strip, sfLineStrip);

    sfVertexArray_append(elem->strip, (sfVertex) {(sfVector2f) {x, y}, sfWhite});
    sfVertexArray_append(elem->strip, (sfVertex) {(sfVector2f) {x + 50, y}, sfWhite});
    sfVertexArray_append(elem->strip, (sfVertex) {(sfVector2f) {x + 50, y + 50}, sfWhite});
    sfVertexArray_append(elem->strip, (sfVertex) {(sfVector2f) {x, y + 50}, sfWhite});

    elem->render = malloc(sizeof(sfRenderStates));
    elem->render->texture = texture;
    elem->render->transform = sfTransform_Identity;
    elem->render->blendMode = sfBlendNone;
    elem->render->shader = NULL;
    return elem;
}

void *calcul_projection (quad_list *elem, float **m1, float **mx)
{
    float **vertex3d1 = multiply1(mx, elem->p1, 3, 1);
    float **vertex3d2 = multiply1(mx, elem->p2, 3, 1);
    float **vertex3d3 = multiply1(mx, elem->p3, 3, 1);
    float **vertex3d4 = multiply1(mx, elem->p4, 3, 1);

    float **vertex2d1 = multiply1(m1, vertex3d1, 3, 1);
    float **vertex2d2 = multiply1(m1, vertex3d2, 3, 1);
    float **vertex2d3 = multiply1(m1, vertex3d3, 3, 1);
    float **vertex2d4 = multiply1(m1, vertex3d4, 3, 1);

    elem->center.x = (vertex3d1[0][0] + vertex3d3[0][0]) / 2;
    elem->center.y = (vertex3d1[1][0] + vertex3d3[1][0]) / 2;
    elem->center.z = (vertex3d1[2][0] + vertex3d3[2][0]) / 2;

    sfVertexArray_getVertex(elem->array, 0)->position.x = vertex2d1[0][0] + 400;
    sfVertexArray_getVertex(elem->array, 0)->position.y = vertex2d1[1][0] + 300;

    sfVertexArray_getVertex(elem->array, 1)->position.x = vertex2d2[0][0] + 400;
    sfVertexArray_getVertex(elem->array, 1)->position.y = vertex2d2[1][0] + 300;

    sfVertexArray_getVertex(elem->array, 2)->position.x = vertex2d3[0][0] + 400;
    sfVertexArray_getVertex(elem->array, 2)->position.y = vertex2d3[1][0] + 300;

    sfVertexArray_getVertex(elem->array, 3)->position.x = vertex2d4[0][0] + 400;
    sfVertexArray_getVertex(elem->array, 3)->position.y = vertex2d4[1][0] + 300;


    sfVertexArray_getVertex(elem->strip, 0)->position.x = vertex2d1[0][0] + 400;
    sfVertexArray_getVertex(elem->strip, 0)->position.y = vertex2d1[1][0] + 300;

    sfVertexArray_getVertex(elem->strip, 1)->position.x = vertex2d2[0][0] + 400;
    sfVertexArray_getVertex(elem->strip, 1)->position.y = vertex2d2[1][0] + 300;

    sfVertexArray_getVertex(elem->strip, 2)->position.x = vertex2d3[0][0] + 400;
    sfVertexArray_getVertex(elem->strip, 2)->position.y = vertex2d3[1][0] + 300;

    sfVertexArray_getVertex(elem->strip, 3)->position.x = vertex2d4[0][0] + 400;
    sfVertexArray_getVertex(elem->strip, 3)->position.y = vertex2d4[1][0] + 300;

    free_matrix(vertex3d1, 3);
    free_matrix(vertex3d2, 3);
    free_matrix(vertex3d3, 3);
    free_matrix(vertex3d4, 3);
    free_matrix(vertex2d1, 3);
    free_matrix(vertex2d2, 3);
    free_matrix(vertex2d3, 3);
    free_matrix(vertex2d4, 3);
}

void update_mesh (quad_list *root, float zoom, float x, float z)
{
    float **mx = combine(combine(x_rotation(x), around_axis(z)), zoom_matrix(zoom));
    float **proj = projection_matrix();
    for (quad_list *ptr = root;ptr != NULL; ptr = ptr->next) {
        calcul_projection(ptr, proj, mx);
        ptr->nbr = sqrt(pow(ptr->center.x, 2) + pow(ptr->center.y, 2) + pow(ptr->center.z - 300, 2));
    }
    free_matrix(mx, 3);
    free_matrix(proj, 3);
}

void free_matrix (float **m, int y)
{
    for (int i = 0;i < y;i++) {
        free(m[i]);
    }
    free(m);
}

int approximation (int i, int j, int delta)
{
    if (i > j - delta && i < j + delta) {
        return 1;
    } else {
        return 0;
    }
}
