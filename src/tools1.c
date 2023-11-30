/*
** EPITECH PROJECT, 2022
** tools1
** File description:
** tools1
*/

#include "../inc/my_world.h"

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