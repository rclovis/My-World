/*
** EPITECH PROJECT, 2021
** my_world
** File description:
** my_world
*/

#include "../inc/my_world.h"

int main (int argc, char **argv)
{
    return my_world(argc, argv);
}

global *setup_global (void)
{
    global *g = malloc(sizeof(global));
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

    // TOOLBAR: Sprite & Texture
    g->tb = setup_toolbar();

    return g;
}

int my_world (int argc, char **argv)
{
    sfVideoMode mode = {800, 600, 32};
    sfRenderWindow *window = sfRenderWindow_create(mode, "my_world", sfResize | sfClose, NULL);
    sfTexture *yes = sfTexture_createFromFile("assets/textures/sand.png", NULL);
    // quad_list *root = create_mesh(1, 1, yes);
    quad_list *root = add_object(root, "src/field.obj", (sfVector2f) {0, 0});
    sfClock *clock = sfClock_create();
    sfEvent event;
    int state = 0, refesh = 1;

    global *g = setup_global();

    float time = 0, zoom = 1, x = 1,  z = 0.3;


    // GAME LOOP
    sfRenderWindow_setFramerateLimit(window, 30);

    while (sfRenderWindow_isOpen(window)) {
        time = sfClock_getElapsedTime(clock).microseconds / 2500000.0;
        (x >= 6.28 || x <= -6.28) ? x = 0 : 0;
        (z >= 6.28 || z <= -6.28) ? z = 0 : 0;

        // SELCTION HOVER
        place_circle(root, (sfVector2i) {-100, -100}, g->vertex);
        place_line(root, (sfVector2i) {-100, -100}, g->bevel);
        place_tile(root, (sfVector2i) {-100, -100}, g->tile);
        if (g->tb->edit_mode == 0)
            place_circle(root, sfMouse_getPositionRenderWindow(window), g->vertex);
        if (g->tb->edit_mode == 1)
            place_line(root, sfMouse_getPositionRenderWindow(window), g->bevel);
        if (g->tb->edit_mode == 2)
            place_tile(root, sfMouse_getPositionRenderWindow(window), g->tile);

        // EVENT POLL
        while (sfRenderWindow_pollEvent(window, &event)) {

            if (event.type == sfEvtMouseButtonReleased)
                if (sfFloatRect_contains(&g->tb->icons_rect[1], event.mouseButton.x, event.mouseButton.y)) {
                    move_toolbar_cursor(g->tb, 0);
                    g->tb->edit_mode = 0;
                }
                else if (sfFloatRect_contains(&g->tb->icons_rect[2], event.mouseButton.x, event.mouseButton.y)) {
                    move_toolbar_cursor(g->tb, 1);
                    g->tb->edit_mode = 1;
                }
                else if (sfFloatRect_contains(&g->tb->icons_rect[3], event.mouseButton.x, event.mouseButton.y)) {
                    move_toolbar_cursor(g->tb, 2);
                    g->tb->edit_mode = 2;
                }
                else
                    (clic_management(&event, root, window, g) == 1) ? refesh = 1 : 0;

            if (event.type == sfEvtKeyPressed) {
                switch (event.key.code) {
                case sfKeyP:
                    toggle_toolbar_visibility(g->tb);
                    break;
                case sfKeyNum1:
                    move_toolbar_cursor(g->tb, 0);
                    g->tb->edit_mode = 0;
                    break;
                case sfKeyNum2:
                    move_toolbar_cursor(g->tb, 1);
                    g->tb->edit_mode = 1;
                    break;
                case sfKeyNum3:
                    move_toolbar_cursor(g->tb, 2);
                    g->tb->edit_mode = 2;
                    break;
                default:
                    break;
                }
            }
            (event.type == sfEvtClosed) ? sfRenderWindow_close(window) : 0;
        }

        // TIME LOOP
        if (time > 0.02) {
            sfRenderWindow_clear(window, sfBlue);
            state = 0;
            if (event.type == sfEvtKeyPressed ||  event.mouseWheel.type == 8) {
                state = 1;
                refesh = 1;
                zoom += event.mouseWheelScroll.delta * 0.1;
                event.mouseWheelScroll.delta = 0;
                (event.key.code == sfKeyUp) ? x -= 0.03 : 0;
                (event.key.code == sfKeyDown) ? x += 0.03 : 0;
                (event.key.code == sfKeyRight) ? z -= 0.03 : 0;
                (event.key.code == sfKeyLeft) ? z += 0.03 : 0;
            }

            (refesh == 1) ? update_mesh(root, zoom, x, z) : 0;
            refesh = 0;
            root = push_swap(root);

            for (quad_list *ptr = root;ptr != NULL; ptr = ptr->next) {
                if (ptr->display == 1) {
                    // if (state == 0)
                        sfRenderWindow_drawVertexArray(window, ptr->array, ptr->render);
                    sfRenderWindow_drawVertexArray(window, ptr->strip, NULL);
                }
            }

            // quad_list *ptr = root;
            // for (int i = 0;i < 1150; ptr = ptr->next, i++) {
            //     if (ptr->display == 1) {
            //         // if (state == 0)
            //         sfRenderWindow_drawVertexArray(window, ptr->array, ptr->render);
            //         sfRenderWindow_drawVertexArray(window, ptr->strip, NULL);
            //     }
            // }

            sfRenderWindow_drawVertexArray(window, g->bevel, NULL);
            sfRenderWindow_drawVertexArray(window, g->tile, NULL);
            sfRenderWindow_drawCircleShape(window, g->vertex, NULL);
            render_toolbar(window, g->tb);
            sfRenderWindow_display(window);
            sfClock_restart(clock);
        }

    }

    // FREE ZONE
    quad_list *test = root;
    while (root != NULL) {
        test = root;
        root = root->next;
        sfVertexArray_destroy(test->array);
        sfVertexArray_destroy(test->strip);
        free_matrix(test->p1, 3);
        free_matrix(test->p2, 3);
        free_matrix(test->p3, 3);
        free(test->render);
        free(test);
    }
    sfVertexArray_destroy(g->tile);
    sfVertexArray_destroy(g->bevel);
    sfCircleShape_destroy(g->vertex);
    free(g);
    sfRenderWindow_destroy(window);
    //

    return 0;
}

quad_list *create_mesh (int x, int y, sfTexture *texture)
{
    quad_list *root = NULL, *ptr = NULL;
    for (int i = 0;i < y;i++) {
        for (int j = 0;j < x;j++) {
            ptr = new_elem(j * 50 - ((x * 50) / 2), i * 50 - ((y * 50) / 2), texture);
            ptr->next->next = root;
            root = ptr;
        }
    }
    return root;
}

quad_list *tri_one (float x, float y, sfTexture *texture)
{
    quad_list *elem = malloc(sizeof(quad_list));

    elem->n_texture = 0;
    elem->center.x = 0;
    elem->center.y = 0;
    elem->center.z = 0;
    elem->display = 1;
    elem->nbr = 0;
    elem->next = NULL;

    elem->p1 = malloc(sizeof(float *) * 4);
    elem->p2 = malloc(sizeof(float *) * 4);
    elem->p3 = malloc(sizeof(float *) * 4);

    elem->p1[0] = malloc(sizeof(float));
    elem->p1[1] = malloc(sizeof(float));
    elem->p1[2] = malloc(sizeof(float));
    elem->p1[0][0] = x;
    elem->p1[1][0] = y + 50;
    elem->p1[2][0] = 0;
    elem->p1[3] = NULL;

    elem->p2[0] = malloc(sizeof(float));
    elem->p2[1] = malloc(sizeof(float));
    elem->p2[2] = malloc(sizeof(float));
    elem->p2[0][0] = x;
    elem->p2[1][0] = y;
    elem->p2[2][0] = 0;
    elem->p2[3] = NULL;

    elem->p3[0] = malloc(sizeof(float));
    elem->p3[1] = malloc(sizeof(float));
    elem->p3[2] = malloc(sizeof(float));
    elem->p3[0][0] = x + 50;
    elem->p3[1][0] = y;
    elem->p3[2][0] = 0;
    elem->p3[3] = NULL;

    elem->array = sfVertexArray_create();
    sfVertexArray_setPrimitiveType(elem->array, sfTriangles);

    sfVertexArray_append(elem->array, (sfVertex) {(sfVector2f) {x, y + 50}, sfWhite, (sfVector2f) {0, 160}});
    sfVertexArray_append(elem->array, (sfVertex) {(sfVector2f) {x, y}, sfWhite, (sfVector2f) {0, 0}});
    sfVertexArray_append(elem->array, (sfVertex) {(sfVector2f) {x + 50, y}, sfWhite, (sfVector2f) {160, 0}});

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

quad_list *tri_two (float x, float y, sfTexture *texture)
{
    quad_list *elem = malloc(sizeof(quad_list));

    elem->n_texture = 0;
    elem->center.x = 0;
    elem->center.y = 0;
    elem->center.z = 0;
    elem->display = 1;
    elem->nbr = 0;
    elem->next = NULL;

    elem->p1 = malloc(sizeof(float *) * 4);
    elem->p2 = malloc(sizeof(float *) * 4);
    elem->p3 = malloc(sizeof(float *) * 4);

    elem->p1[0] = malloc(sizeof(float));
    elem->p1[1] = malloc(sizeof(float));
    elem->p1[2] = malloc(sizeof(float));
    elem->p1[0][0] = x + 50;
    elem->p1[1][0] = y;
    elem->p1[2][0] = 0;
    elem->p1[3] = NULL;

    elem->p2[0] = malloc(sizeof(float));
    elem->p2[1] = malloc(sizeof(float));
    elem->p2[2] = malloc(sizeof(float));
    elem->p2[0][0] = x + 50;
    elem->p2[1][0] = y + 50;
    elem->p2[2][0] = 0;
    elem->p2[3] = NULL;

    elem->p3[0] = malloc(sizeof(float));
    elem->p3[1] = malloc(sizeof(float));
    elem->p3[2] = malloc(sizeof(float));
    elem->p3[0][0] = x;
    elem->p3[1][0] = y + 50;
    elem->p3[2][0] = 0;
    elem->p3[3] = NULL;

    elem->array = sfVertexArray_create();
    sfVertexArray_setPrimitiveType(elem->array, sfTriangles);

    sfVertexArray_append(elem->array, (sfVertex) {(sfVector2f) {x + 50, y}, sfWhite, (sfVector2f) {160, 0}});
    sfVertexArray_append(elem->array, (sfVertex) {(sfVector2f) {x + 50, y + 50}, sfWhite, (sfVector2f) {160, 160}});
    sfVertexArray_append(elem->array, (sfVertex) {(sfVector2f) {x, y + 50}, sfWhite, (sfVector2f) {0, 160}});

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

quad_list *new_elem (float x, float y, sfTexture *texture)
{
    quad_list *elem = tri_one(x, y, texture);
    elem->next = tri_two(x, y, texture);
    return elem;
}


void calcul_projection (quad_list *elem, float **m1, float **mx)
{
    float **vertex2d1 = multiply1(m1, elem->p1, 2, 1);
    float **vertex2d2 = multiply1(m1, elem->p2, 2, 1);
    float **vertex2d3 = multiply1(m1, elem->p3, 2, 1);

    sfVertexArray_getVertex(elem->array, 0)->position.x = vertex2d1[0][0] + 400;
    sfVertexArray_getVertex(elem->array, 0)->position.y = vertex2d1[1][0] + 300;

    sfVertexArray_getVertex(elem->array, 1)->position.x = vertex2d2[0][0] + 400;
    sfVertexArray_getVertex(elem->array, 1)->position.y = vertex2d2[1][0] + 300;

    sfVertexArray_getVertex(elem->array, 2)->position.x = vertex2d3[0][0] + 400;
    sfVertexArray_getVertex(elem->array, 2)->position.y = vertex2d3[1][0] + 300;


    sfVertexArray_getVertex(elem->strip, 0)->position.x = vertex2d1[0][0] + 400;
    sfVertexArray_getVertex(elem->strip, 0)->position.y = vertex2d1[1][0] + 300;

    sfVertexArray_getVertex(elem->strip, 1)->position.x = vertex2d2[0][0] + 400;
    sfVertexArray_getVertex(elem->strip, 1)->position.y = vertex2d2[1][0] + 300;

    sfVertexArray_getVertex(elem->strip, 2)->position.x = vertex2d3[0][0] + 400;
    sfVertexArray_getVertex(elem->strip, 2)->position.y = vertex2d3[1][0] + 300;

    sfVertexArray_getVertex(elem->strip, 3)->position.x = vertex2d1[0][0] + 400;
    sfVertexArray_getVertex(elem->strip, 3)->position.y = vertex2d1[1][0] + 300;


    if (vertex2d1[0][0] < -400 || vertex2d1[0][0] > 400 || vertex2d1[1][0] < -300 || vertex2d1[1][0] > 300) {
        if (vertex2d2[0][0] < -400 || vertex2d2[0][0] > 400 || vertex2d2[1][0] < -300 || vertex2d2[1][0] > 300) {
            if (vertex2d3[0][0] < -400 || vertex2d3[0][0] > 400 || vertex2d3[1][0] < -300 || vertex2d3[1][0] > 300) {
                elem->display = 0;
                free_matrix(vertex2d1, 3);
                free_matrix(vertex2d2, 3);
                free_matrix(vertex2d3, 3);
                return;
            }
        }
    }
    elem->display = 1;

    float **vertex3d1 = multiply1(mx, elem->p1, 3, 1);
    float **vertex3d2 = multiply1(mx, elem->p2, 3, 1);
    float **vertex3d3 = multiply1(mx, elem->p3, 3, 1);

    sfVector3f h_c;
    h_c.x = (vertex3d1[0][0] + vertex3d3[0][0]) / 2;
    h_c.y = (vertex3d1[1][0] + vertex3d3[1][0]) / 2;
    h_c.z = (vertex3d1[2][0] + vertex3d3[2][0]) / 2;

    elem->center.x = (h_c.x + vertex3d2[0][0]) / 2;
    elem->center.y = (h_c.y + vertex3d2[1][0]) / 2;
    elem->center.z = (h_c.z + vertex3d2[2][0]) / 2;

    free_matrix(vertex3d1, 3);
    free_matrix(vertex3d2, 3);
    free_matrix(vertex3d3, 3);

    free_matrix(vertex2d1, 3);
    free_matrix(vertex2d2, 3);
    free_matrix(vertex2d3, 3);
}

void update_mesh (quad_list *root, float zoom, float x, float z)
{
    float **mx = position_matrix(x, z, zoom);
    float **temp = projection_matrix();
    float **proj = multiply1(temp, mx, 3, 3);
    for (quad_list *ptr = root;ptr != NULL; ptr = ptr->next) {
        calcul_projection(ptr, proj, mx);
        ptr->nbr = sqrt(pow(ptr->center.x, 2) + pow(ptr->center.y, 2) + pow(ptr->center.z - (1000 * 1 / zoom), 2));
        // if (ptr->n_texture == 333)
        // printf("%d\n", ptr->nbr);
    }
    free_matrix(mx, 3);
    free_matrix(proj, 3);
    free_matrix(temp, 3);
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
