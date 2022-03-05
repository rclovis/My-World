/*
** EPITECH PROJECT, 2021
** my_world
** File description:
** my_world
*/

#include "../inc/my_world.h"

int main (int argc, char **argv)
{
    return my_world(argc, argv, spinning_menu(1));
}



//expérimental donc pas encore propre
//en gros c ce qui va permettre de faire tourner un modèle dans le menu
//avec 1 en argument, ça fait tourner amogus et avec 0 ça fait tourner une map
//du coup il faudra penser à créer une map sympa à faire tourner dans le menu
sfRenderWindow *spinning_menu (int v)
{
    sfVideoMode mode = {800, 600, 32};
    sfRenderWindow *window = sfRenderWindow_create(mode, "my_world", sfResize | sfClose, NULL);
    quad_list *root = NULL;
    float time = 0, zoom = 1, x = 1,  z = 0;
    if (v == 1) {
        root = add_object(root, "assets/3d_objects/untitledi.obj", (sfVector3f) {-7, -7, -23});
        x = 1.57;
    } else {
        root = loat_file(root, "save");
        z = 0.3;
    }
    sfClock *clock = sfClock_create();
    sfEvent event;
    global *g = setup_global();
    sfRenderWindow_setFramerateLimit(window, 30);
    while (sfRenderWindow_isOpen(window)) {
        time = sfClock_getElapsedTime(clock).microseconds / 2500000.0;
        (x >= 6.28 || x <= -6.28) ? x = 0 : 0;
        while (sfRenderWindow_pollEvent(window, &event))
            (event.type == sfEvtClosed) ? sfRenderWindow_close(window) : 0;
        if (time > 0.01) {
            z += (v == 1) ? 0.05 : 0.01;
            sfRenderWindow_clear(window, sfBlue);

            update_mesh(root, zoom, x, z);
            root = push_swap(root);

            for (quad_list *ptr = root;ptr != NULL; ptr = ptr->next) {
                if (ptr->display == 1) {
                    sfRenderWindow_drawVertexArray(window, ptr->array, ptr->render);
                    sfRenderWindow_drawVertexArray(window, ptr->strip, NULL);
                }
            }
            sfRenderWindow_display(window);
            sfClock_restart(clock);
        }

    }
    free_quad_list(root);
    free(g);
    return 0;
}
//

//faut revoir du début cette merde
void event_poll (sfEvent event, global *g, quad_list *root, sfRenderWindow *window)
{
    if (event.type == sfEvtMouseButtonReleased) {
        if (sfFloatRect_contains(&g->tb->icons_rect[1], event.mouseButton.x, event.mouseButton.y)) {
            move_toolbar_cursor(g->tb, 0);
            g->tb->edit_mode = 0;
        } else if (sfFloatRect_contains(&g->tb->icons_rect[2], event.mouseButton.x, event.mouseButton.y)) {
            move_toolbar_cursor(g->tb, 1);
            g->tb->edit_mode = 1;
        } else if (sfFloatRect_contains(&g->tb->icons_rect[3], event.mouseButton.x, event.mouseButton.y)) {
            move_toolbar_cursor(g->tb, 2);
            g->tb->edit_mode = 2;
        } else
            (clic_management(&event, root, window, g) == 1) ? g->refresh = 1 : 0;
    }
    if (event.type == sfEvtKeyPressed) {
        switch (event.key.code) {
        case sfKeyP:
            toggle_toolbar_visibility(g->tb);
            break;
        case sfKeyNumpad1:
            move_toolbar_cursor(g->tb, 0);
            g->tb->edit_mode = 0;
            break;
        case sfKeyNumpad2:
            move_toolbar_cursor(g->tb, 1);
            g->tb->edit_mode = 1;
            break;
        case sfKeyNumpad3:
            move_toolbar_cursor(g->tb, 2);
            g->tb->edit_mode = 2;
            break;
        case sfKeyNumpad4:
            move_toolbar_cursor(g->tb, 3);
            g->tb->edit_mode = 3;
            break;
        case sfKeyNumpad5:
            move_toolbar_cursor(g->tb, 4);
            g->tb->edit_mode = 4;
            break;
        case sfKeyNumpad6:
            save_file(root, "save");
            break;
        default:
            break;
        }
    }
}
//


//on peut encore bcp séquencer mais comme je pense qu'on va ajouter && modifier des choses...
int my_world (int argc, char **argv, sfRenderWindow *w)
{
    sfVideoMode mode = {800, 600, 32};
    sfRenderWindow *window = sfRenderWindow_create(mode, "my_world", sfResize | sfClose, NULL);
    sfTexture *yes = sfTexture_createFromFile("assets/textures/textures.png", NULL);
    quad_list *root = create_mesh(10, 10, (sfVector3f) {0, 0, 0}, NULL);
    // root = create_mesh(4, 5, (sfVector3f) {50, 50, 50}, root);
    // quad_list *root = add_object(root, "assets/3d_objects/untitledi.obj", (sfVector2f) {0, 0});
    // root = add_object(root, "assets/3d_objects/detail_treeLarge.obj", (sfVector3f) {5, 5, 1});

    // quad_list *root = loat_file(root, "save");

    sfClock *clock = sfClock_create();
    sfEvent event;

    global *g = setup_global();

    float time = 0, zoom = 1, x = 1,  z = 0.3;

    // GAME LOOP
    sfRenderWindow_setFramerateLimit(window, 30);
    while (sfRenderWindow_isOpen(window)) {
        display_fps(g->fps);
        time = sfClock_getElapsedTime(clock).microseconds / 2500000.0;

        // SELCTION HOVER
        place_circle(root, (sfVector2i) {-100, -100}, g->vertex);
        place_line(root, (sfVector2i) {-100, -100}, g->bevel);
        place_tile(root, (sfVector2i) {-100, -100}, g->tile);
        if (g->tb->edit_mode == 0)
            place_circle(root, sfMouse_getPositionRenderWindow(window), g->vertex);
        if (g->tb->edit_mode == 1)
            place_line(root, sfMouse_getPositionRenderWindow(window), g->bevel);
        if (g->tb->edit_mode == 2 || g->tb->edit_mode == 4)
            place_tile(root, sfMouse_getPositionRenderWindow(window), g->tile);

        // EVENT POLL
        while (sfRenderWindow_pollEvent(window, &event)) {
            event_poll(event, g, root, window);
            (event.type == sfEvtClosed) ? sfRenderWindow_close(window) : 0;
        }

        // TIME LOOP
        if (time > 0.01) {
            g->fps->frames++;
            sfRenderWindow_clear(window, sfBlue);
            g->state = 0;
            if (event.type == sfEvtKeyPressed ||  event.mouseWheel.type == 8) {
                g->state = 1;
                g->refresh = 1;
                zoom += event.mouseWheelScroll.delta * 0.1;
                event.mouseWheelScroll.delta = 0;
                (event.key.code == sfKeyUp) ? x -= 0.03 : 0;
                (event.key.code == sfKeyDown) ? x += 0.03 : 0;
                (event.key.code == sfKeyRight) ? z -= 0.03 : 0;
                (event.key.code == sfKeyLeft) ? z += 0.03 : 0;
            }

            (g->refresh == 1) ? update_mesh(root, zoom, x, z) : 0;
            (g->refresh == 1) ? root = push_swap(root) : 0;
            g->refresh = 0;

            for (quad_list *ptr = root;ptr != NULL; ptr = ptr->next) {
                if (ptr->display == 1) {
                    if (g->state == 0)
                        sfRenderWindow_drawVertexArray(window, ptr->array, ptr->render);
                    sfRenderWindow_drawVertexArray(window, ptr->strip, NULL);
                }
            }

            sfRenderWindow_drawText(window, g->fps->text, NULL);
            sfRenderWindow_drawVertexArray(window, g->bevel, NULL);
            sfRenderWindow_drawVertexArray(window, g->tile, NULL);
            sfRenderWindow_drawCircleShape(window, g->vertex, NULL);
            render_toolbar(window, g->tb);
            sfRenderWindow_display(window);
            sfClock_restart(clock);
        }

    }

    // FREE ZONE
    free_quad_list(root);
    sfVertexArray_destroy(g->tile);
    sfVertexArray_destroy(g->bevel);
    sfCircleShape_destroy(g->vertex);
    free(g);
    sfRenderWindow_destroy(window);
    //

    return 0;
}

global *setup_global (void)
{
    global *g = malloc(sizeof(global));
    g->apply_mode = 0;
    g->refresh = 1;
    g->state = 0;
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

    // TOOLBAR: Sprite & Texture
    g->tb = setup_toolbar();

    // FPS: clock text font counter
    g->fps = fps_init();

    return g;
}

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


//pour vérifier si un triangle est hors screen ou pas
int is_in_screen (float **v1, float **v2, float **v3, quad_list *elem)
{
    int e = 0;
    if (v1[0][0] < -400 || v1[0][0] > 400 || v1[1][0] < -300 || v1[1][0] > 300)
        e++;
    if (v2[0][0] < -400 || v2[0][0] > 400 || v2[1][0] < -300 || v2[1][0] > 300)
        e++;
    if (v3[0][0] < -400 || v3[0][0] > 400 || v3[1][0] < -300 || v3[1][0] > 300)
        e++;
    free_matrix(v1, 3);
    free_matrix(v2, 3);
    free_matrix(v3, 3);
    if (e == 3) {
        elem->display = 0;
        return (0);
    }
    return (1);
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
    if (is_in_screen(vertex2d1, vertex2d2, vertex2d3, elem) == 0) return;
    compute_centre(mx, elem);
}

int compute_centre (float **mx, quad_list *elem)
{
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
}

void update_mesh (quad_list *root, float zoom, float x, float z)
{
    float **mx = position_matrix(x, z, zoom);
    float **temp = projection_matrix();
    float **proj = multiply1(temp, mx, 3, 3);
    for (quad_list *ptr = root;ptr != NULL; ptr = ptr->next) {
        calcul_projection(ptr, proj, mx);
        ptr->nbr = pow(ptr->center.x, 2);
        ptr->nbr += pow(ptr->center.y, 2);
        ptr->nbr += pow(ptr->center.z - (1000 * 1 / zoom), 2);
        ptr->nbr = sqrt(ptr->nbr);
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

int free_quad_list (quad_list *root)
{
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
    return (0);
}
