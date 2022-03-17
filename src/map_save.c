/*
** EPITECH PROJECT, 2022
** map_save
** File description:
** map_save
*/

#include "../inc/my_world.h"

char *float_to_str (double nbr)
{
    char *result = NULL, *temp = NULL;
    if (nbr >= 0) {
        temp = int_to_char(floor(nbr / 1));
        result = my_strcat(temp, ".");
        free(temp);
        temp = int_to_char((nbr - floor(nbr / 1)) / 0.00001);
        result = my_strcat(result, temp);
        free(temp);
    }
    if (nbr < 0) {
        nbr *= -1;
        temp = int_to_char(floor(nbr / 1));
        result = my_strcat("-", temp);
        free(temp);
        result = my_strcat(result, ".");
        temp = int_to_char((nbr - floor(nbr / 1)) / 0.00001);
        result = my_strcat(result, temp);
        free(temp);
    }
    return result;
}

int save_file (quad_list *root, char *name)
{
    char *line = NULL, *t = NULL;
    int len = 0;
    FILE *stream = fopen(name, "w");
    for (quad_list *p = root;p != NULL;p = p->next, free(t)) {
        save_points(p, stream);
        for (int i = 0;i < 3;fwrite(" ", 1, 1, stream), i++) {
            t = float_to_str(sfVertexArray_getVertex(p->array, i)->texCoords.x);
            fwrite(t, my_strlen(t), 1, stream);
            free(t);
            fwrite(" ", 1, 1, stream);
            t = float_to_str(sfVertexArray_getVertex(p->array, i)->texCoords.y);
            fwrite(t, my_strlen(t), 1, stream);
            free(t);
        }
        t = int_to_char(p->n_texture);
        fwrite(t, my_strlen(t), 1, stream);
        fwrite("\n", 1, 1, stream);
    }
    return 0;
}

int save_points (quad_list *ptr, FILE *stream)
{
    char *temp = NULL;
    fwrite("  ", 2, 1, stream);
    for (int i = 0;i < 3;i++) {
        temp = float_to_str(ptr->p1[i][0]);
        fwrite(temp, my_strlen(temp), 1, stream);
        free(temp);
        fwrite(" ", 1, 1, stream);
    }
    for (int i = 0;i < 3;i++) {
        temp = float_to_str(ptr->p2[i][0]);
        fwrite(temp, my_strlen(temp), 1, stream);
        free(temp);
        fwrite(" ", 1, 1, stream);
    }
    for (int i = 0;i < 3;i++) {
        temp = float_to_str(ptr->p3[i][0]);
        fwrite(temp, my_strlen(temp), 1, stream);
        free(temp);
        fwrite(" ", 1, 1, stream);
    }
}

quad_list *load_file (quad_list *root, char *file)
{
    char **object = file_str(file), **t = NULL;
    if (object == NULL) return NULL;
    quad_list *ptr = NULL;
    sfTexture *tx = sfTexture_createFromFile("assets/textures/textures.png", 0);
    for (int i = 0;object[i] != NULL;ptr->next = root, root = ptr, i++) {
        t = my_2d_array_str_split(&object[i][2], ' ');
        ptr = tri_one(0, 0, 0, 0);
        sfVertexArray_getVertex(ptr->array, 0)->texCoords.x = my_getnbr2(t[9]);
        sfVertexArray_getVertex(ptr->array, 0)->texCoords.y = my_getnbr2(t[10]);
        sfVertexArray_getVertex(ptr->array, 1)->texCoords.x = my_getnbr2(t[11]);
        sfVertexArray_getVertex(ptr->array, 1)->texCoords.y = my_getnbr2(t[12]);
        sfVertexArray_getVertex(ptr->array, 2)->texCoords.x = my_getnbr2(t[13]);
        sfVertexArray_getVertex(ptr->array, 2)->texCoords.y = my_getnbr2(t[14]);
        for (int i = 0;i < 3;ptr->p1[i][0] = atof(t[i]), i++);
        for (int i = 0;i < 3;ptr->p2[i][0] = atof(t[i + 3]), i++);
        for (int i = 0;i < 3;ptr->p3[i][0] = atof(t[i + 6]), i++);
        ptr->n_texture = my_getnbr2(t[15]);
        ptr->render->texture = tx;
    }
    return root;
}

int coding_style2 (sfVector2f v1, sfVector2f v2, sfVertexArray *bevel)
{
    sfVertexArray_getVertex(bevel, 0)->position = v1;
    sfVertexArray_getVertex(bevel, 1)->position = v2;
}
