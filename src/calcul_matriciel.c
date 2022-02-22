/*
** EPITECH PROJECT, 2022
** calcul matricel
** File description:
** calcul matricel
*/

#include "../inc/my_world.h"

float **combine (float **m1, float **m2)
{
    float **m3 = multiply1(m1, m2, 3, 3);
    free(m1);
    free(m2);
    return m3;
}

float **multiply1 (float **m1, float **m2, int ligne_m1, int col_m2)
{
    float **result = malloc(sizeof(float *) * (ligne_m1 + 1));
    result[ligne_m1] = NULL;
    for (int y = 0;y < ligne_m1;y++) {
        result[y] = malloc(sizeof(float) * col_m2);
        for (int x = 0;x < col_m2;x++) {
            result[y][x] = multiply2(m1, m2, x, y);
        }
    }
    return result;
}

float multiply2 (float **m1, float **m2, int x, int y)
{
    float result = 0;
    for (int i = 0;m2[i] != NULL;i++) {
        result += m1[y][i] * m2[i][x];
    }
    return result;
}
