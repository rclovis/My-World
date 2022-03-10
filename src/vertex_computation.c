/*
** EPITECH PROJECT, 2022
** vertex computation
** File description:
** vertex computation
*/

#include "../inc/my_world.h"

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
