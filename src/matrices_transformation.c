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

float **zoom_matrix (float zoom)
{
    float *l1 = malloc(sizeof(float) * 3), *l2 = malloc(sizeof(float) * 3);
    float *l3 = malloc(4 * 3), **m3 = malloc(8 * 4), **result;
    l1[0] = zoom;
    l1[1] = 0;
    l1[2] = 0;
    l2[0] = 0;
    l2[1] = zoom;
    l2[2] = 0;
    l3[0] = 0;
    l3[1] = 0;
    l3[2] = zoom;
    m3[0] = l1;
    m3[1] = l2;
    m3[2] = l3;
    m3[3] = NULL;
    return m3;
}

float **around_axis (float z)
{
    float *l1 = malloc(sizeof(float) * 3), *l2 = malloc(sizeof(float) * 3);
    float *l3 = malloc(4 * 3), **m3 = malloc(8 * 4), **result;
    l1[0] = cos(z);
    l1[1] = sin(z);
    l1[2] = 0;
    l2[0] = - sin(z);
    l2[1] = cos(z);
    l2[2] = 0;
    l3[0] = 0;
    l3[1] = 0;
    l3[2] = 1;
    m3[0] = l1;
    m3[1] = l2;
    m3[2] = l3;
    m3[3] = NULL;
    return m3;
}

float **x_rotation (float r)
{
    float *l1 = malloc(sizeof(float) * 3), *l2 = malloc(sizeof(float) * 3);
    float *l3 = malloc(4 * 3), **m3 = malloc(8 * 4), **result;
    l1[0] = 1;
    l1[1] = 0;
    l1[2] = 0;
    l2[0] = 0;
    l2[1] = cos(r);
    l2[2] = - sin(r);
    l3[0] = 0;
    l3[1] = sin(r);
    l3[2] = cos(r);
    m3[0] = l1;
    m3[1] = l2;
    m3[2] = l3;
    m3[3] = NULL;
    return m3;
}

// float **test (float r, float z)
// {
//     float *l1 = malloc(sizeof(float) * 3), *l2 = malloc(sizeof(float) * 3);
//     float *l3 = malloc(4 * 3), **m3 = malloc(8 * 4), **result;
//     l1[0] = cos(z);
//     l1[1] = sin(z);
//     l1[2] = 0;

//     l2[0] = cos(r) * -sin(z);
//     l2[1] = cos(r) * cos(z);
//     l2[2] = -sin(r);

//     l3[0] = sin(r) * -sin(z);
//     l3[1] = sin(r) * cos(z);
//     l3[2] = cos(r);
//     m3[0] = l1;
//     m3[1] = l2;
//     m3[2] = l3;
//     m3[3] = NULL;
//     return m3;
// }
