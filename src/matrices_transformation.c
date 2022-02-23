/*
** EPITECH PROJECT, 2022
** matrices transformation
** File description:
** matrices transformation
*/

#include "../inc/my_world.h"


float **projection_matrix (void)
{
    float *l1 = malloc(sizeof(float) * 3), *l2 = malloc(sizeof(float) * 3);
    float *l3 = malloc(4 * 3), **m3 = malloc(8 * 4), **result;
    l1[0] = 1;
    l1[1] = 0;
    l1[2] = 0;
    l2[0] = 0;
    l2[1] = 1;
    l2[2] = 0;
    l3[0] = 0;
    l3[1] = 0;
    l3[2] = 0;
    m3[0] = l1;
    m3[1] = l2;
    m3[2] = l3;
    m3[3] = NULL;
    return m3;
}

float **view_matrix (void)
{
    float *l1 = malloc(sizeof(float)), *l2 = malloc(sizeof(float));
    float *l3 = malloc(4), **m3 = malloc(8 * 4), **result;
    l1[0] = 50;
    l2[0] = 50;
    l3[0] = 300;
    m3[0] = l1;
    m3[1] = l2;
    m3[2] = l3;
    m3[3] = NULL;
    return m3;
}

float **position_matrix (float x, float z, float zoom)
{
    float *l1 = malloc(sizeof(float) * 3), *l2 = malloc(sizeof(float) * 3);
    float *l3 = malloc(4 * 3), **m3 = malloc(8 * 4), **result;
    l1[0] = cos(z) * zoom;
    l1[1] = sin(z) * zoom;
    l1[2] = 0;
    l2[0] = cos(x) * -sin(z) * zoom;
    l2[1] = cos(x) * cos(z) * zoom;
    l2[2] = -sin(x) * zoom;
    l3[0] = sin(x) * -sin(z);
    l3[1] = sin(x) * cos(z);
    l3[2] = cos(x) * zoom;
    m3[0] = l1;
    m3[1] = l2;
    m3[2] = l3;
    m3[3] = NULL;
    return m3;
}
