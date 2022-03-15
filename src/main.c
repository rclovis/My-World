/*
** EPITECH PROJECT, 2021
** my_world
** File description:
** my_world
*/

#include "../inc/my_world.h"

int main (int argc, char **argv)
{
    char *name;
    quad_list *root;
    sfRenderWindow *w = spinning_menu(1, &name, &root);
    return my_world(w, name, root);
}

//expérimental donc pas encore propre
//en gros c ce qui va permettre de faire tourner un modèle dans le menu
//avec 1 en argument, ça fait tourner amogus et avec 0 ça fait tourner une map
//du coup il faudra penser à créer une map sympa à faire tourner dans le menu
sfRenderWindow *spinning_menu (int v, char **file, quad_list **to_send)
{
    sfVideoMode mode = {800, 600, 32};
    sfRenderWindow *window = sfRenderWindow_create(mode, "my_world", sfResize | sfClose, NULL);
    quad_list *root = NULL;
    float time = 0, zoom = 1, x = 1,  z = 0;
    if (v == 1) {
        root = add_object(root, "assets/3d_objects/amogus", (sfVector3f) {-7, -7, -23});
        x = 1.57;
    } else {
        root = loat_file(root, "save");
        z = 0.3;
    }
    sfClock *clock = sfClock_create();
    sfEvent event;
    global *g = setup_global();
    g->curr_menu->data = M_MAIN;
    g->is_typing = 0;
    sfRenderWindow_setFramerateLimit(window, 60);
    while (sfRenderWindow_isOpen(window)) {
        while (sfRenderWindow_pollEvent(window, &event)) {
            menu_evt(g, &event, window);
            (event.type == sfEvtClosed) ? sfRenderWindow_close(window) : 0;
        }


        if (g->curr_menu == NULL || g->complete2 == 1 || g->complete == 1 && g->id_menu == 1) {
            char *name = malloc(sizeof(char) * 21);
            name[20] = '\0';
            for (int i = 0; i < 20; i++)
                name[i] = g->input_buffer[i];
            *file = my_strcat("assets/3d_objects/", name);
            if (v == 1) {
                *to_send = add_object(NULL, "assets/3d_objects/amogus", (sfVector3f) {-7, -7, -23});
                return (window);
            }
            if (g->complete2 == 1) {
                *to_send = create_mesh(g->x, g->y, (sfVector3f) {0, 0, 0}, NULL);
            }
            if (g->complete == 1 && g->id_menu == 1) {
                *to_send = loat_file(*to_send, name);
            }
            return (window);
        }


        time = sfClock_getElapsedTime(clock).microseconds / 2500000.0;
        g->is_typing = (g->curr_menu->data == M_INPUT) ? 1 : 0;
        if (g->complete == 1 && g->id_menu == 0 && g->curr_menu->data == 3)
            g->curr_menu = callstack_add(g->curr_menu, M_COORDS);
        if (time > 0.00001) {
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
            render_menu(window, g);
            sfRenderWindow_display(window);
            sfClock_restart(clock);
        }
    }
    free_quad_list(root);
    free(g);
    return 0;
}
//

//j'ai mis ça a la norme
//en gros si tu veux ajouter un outils dans ta tool bar t'as juste a ajouter son keycode dans le tableau "buttons" && modifier la valeur d'arrêt
//du i dans le premier for donc si on a trois outils tu met i < 3
void event_poll (sfEvent event, global *g, quad_list *root, sfRenderWindow *w)
{
    int buttons[5] = {76, 77, 78, 79, 80}, b = 0;
    int x = event.mouseButton.x, y = event.mouseButton.y;
    int is_clicking = (event.type == sfEvtMouseButtonReleased) ? 1 : 0;
    for (int i = 0;i < 3 && is_clicking == 1;i++) {
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
//


//on peut encore bcp séquencer mais comme je pense qu'on va ajouter && modifier des choses...
int my_world (sfRenderWindow *window, char *file, quad_list *root)
{


    sfClock *clock = sfClock_create();
    sfEvent event;

    global *g = setup_global();

    float time = 0, zoom = 1, x = 1,  z = 0.3;

    // GAME LOOP
    sfRenderWindow_setFramerateLimit(window, 60);
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
        if (time > 0.00000000001) {
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
    g->id_menu = 0;
    g->complete = 0;
    g->x = 1;
    g->y = 1;
    g->vertex = sfCircleShape_create();
    sfCircleShape_setRadius(g->vertex, 5);
    sfCircleShape_setFillColor(g->vertex, sfBlack);
    sfCircleShape_setOrigin(g->vertex, (sfVector2f) {5, 5});

    g->bevel = sfVertexArray_create();
    sfVertexArray_setPrimitiveType(g->bevel, sfLines);
    sfVertexArray_append(g->bevel, (sfVertex) {(sfVector2f) {-100, -100}, sfBlack});
    sfVertexArray_append(g->bevel, (sfVertex) {(sfVector2f) {-100, -100}, sfBlack});

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

    // MENU
    g->is_typing = 0;
    g->curr_menu = callstack_init();
    g->cursor = 0;
    g->pixel_font = sfFont_createFromFile("assets/fonts/pixel.ttf");
    g->button_texture = sfTexture_createFromFile("assets/gui/button.png", NULL);
    g->main_menu = main_menu_init(g->pixel_font, g->button_texture);
    g->input_menu = input_menu_init(g->pixel_font, g->button_texture);
    g->pause_menu = pause_menu_init(g->pixel_font, g->button_texture);
    g->coords_menu = coords_menu_init(g->pixel_font, g->button_texture);
    for (int i = 0; i < INPUT_BUFFER_SIZE; i++)
        g->input_buffer[i] = 0;

    return g;
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
