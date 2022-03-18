/*
** EPITECH PROJECT, 2022
** tools3
** File description:
** tools3
*/

#include "../inc/my_world.h"

char **file_str (char *file_name)
{
    int h = 0, return_val = 0;
    size_t len = 0;
    FILE *f = fopen(file_name, "r");
    if (f == NULL) return NULL;
    word *root = malloc(sizeof(word)), *p = root, *temp = root;
    for (;return_val != -1;h++, p->next = NULL) {
        p->str = NULL;
        return_val = getline(&(p->str), &len, f);
        if (return_val != -1) {
            p->next = malloc(sizeof(word));
            temp = p;
            p = p->next;
        }
    }
    temp->next = NULL;
    p = root;
    char **result = malloc(sizeof(char *) * h);
    for (int i = 0;p != NULL;result[i] = p->str, p = p->next, i++);
    result[h - 1] = NULL;
    return (result);
}

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

global *setup_global (char *name, quad_list *root, int bool)
{
    global *g = malloc(sizeof(global));
    setup_global3(g);
    g->root = root;
    g->name = name;
    setup_global2(g, bool);
    g->zoom = 1;
    g->x = 1;
    g->z = 0;
    g->v = bool;
    g->curr_menu = callstack_init();
    g->pixel_font = sfFont_createFromFile("assets/fonts/pixel.ttf");
    g->button_texture = sfTexture_createFromFile("assets/gui/button.png", NULL);
    g->main_menu = main_menu_init(g->pixel_font, g->button_texture);
    g->input_menu = input_menu_init(g->pixel_font, g->button_texture);
    g->pause_menu = pause_menu_init(g->pixel_font, g->button_texture);
    g->coords_menu = coords_menu_init(g->pixel_font, g->button_texture);
    g->is_typing = 0;
    for (int i = 0; i < INPUT_BUFFER_SIZE; i++)
        g->input_buffer[i] = 0;
    return g;
}

void setup_global2 (global *g, int bool)
{
    g->vertex = sfCircleShape_create();
    sfCircleShape_setRadius(g->vertex, 5);
    sfCircleShape_setFillColor(g->vertex, sfBlack);
    sfCircleShape_setOrigin(g->vertex, (sfVector2f) {5, 5});
    g->bevel = sfVertexArray_create();
    sfVertexArray_setPrimitiveType(g->bevel, sfLines);
    sfVertexArray_append(g->bevel, (sfVertex) {(sfVector2f) {-1, -1}, sfBlack});
    sfVertexArray_append(g->bevel, (sfVertex) {(sfVector2f) {-1, -1}, sfBlack});
    g->tile = sfVertexArray_create();
    sfVertexArray_setPrimitiveType(g->tile, sfLinesStrip);
    sfVertexArray_append(g->tile, (sfVertex) {(sfVector2f) {-1, -1}, sfBlack});
    sfVertexArray_append(g->tile, (sfVertex) {(sfVector2f) {-1, -1}, sfBlack});
    sfVertexArray_append(g->tile, (sfVertex) {(sfVector2f) {-1, -1}, sfBlack});
    sfVertexArray_append(g->tile, (sfVertex) {(sfVector2f) {-1, -1}, sfBlack});
    g->tb = setup_toolbar();
    g->fps = fps_init();
    if (bool == 1)
        g->click = sfMusic_createFromFile("assets/sounds/click1.ogg");
    else
        g->click = sfMusic_createFromFile("assets/sounds/click2.ogg");
}

void setup_global3 (global *g)
{
    g->x2 = 1;
    g->apply_mode = 0;
    g->refresh = 1;
    g->state = 0;
    g->id_menu = 0;
    g->complete = 0;
    g->complete2 = 0;
    g->cursor = 0;
    g->is_typing = 0;
    g->x = 1;
    g->y = 1;
}
