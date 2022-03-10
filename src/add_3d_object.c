/*
** EPITECH PROJECT, 2022
** add_3d_object
** File description:
** add_3d_object
*/

#include "../inc/my_world.h"

linked_vertex *get_vertex (char **object, sfVector3f pos)
{
    char **temp = NULL;
    linked_vertex *root = malloc(sizeof(linked_vertex));
    linked_vertex *ptr = root;
    root->next = NULL;
    for (int i = 0;object[i] != NULL;i++) {
        if (object[i][0] == 'v' && object[i][1] == ' ') {
            temp = my_2d_array_str_split(&object[i][2], ' ');
            ptr->next = malloc(sizeof(linked_vertex));
            ptr = ptr->next;
            ptr->next = NULL;
            ptr->x = my_atof(temp[0]) + pos.x;
            ptr->y = my_atof(temp[1]) + pos.z;
            ptr->z = my_atof(temp[2]) + pos.y;
            free(temp[0]);
            free(temp[1]);
            free(temp[2]);
            free(temp);
        }
    }
    return (root->next);
}

linked_vertex *hook_vertex (linked_vertex *root, int i)
{
    linked_vertex *ptr = root;
    for (int j = 0;j < i - 1;j++) {
        ptr = ptr->next;
    }
    return ptr;
}

quad_list *add_object (quad_list *root, char *file, sfVector3f pos)
{
    char **object = file_str(file), **temp = NULL;
    quad_list *ptr = NULL;
    float **zoom = multiply1(x_rotation(1.57), zoom_matrix(15), 3, 3), **mx = 0;
    linked_vertex *vertex_list = get_vertex(object, pos), *hook = NULL;
    for (int i = 0;object[i] != NULL;i++) {
        if (object[i][0] == 'f') {
            temp = my_2d_array_str_split(&object[i][2], ' ');
            ptr = tri_one(0, 0, 0, NULL);
            ptr->p1 = set_hooked_point(vertex_list, temp, ptr, 0);
            ptr->p2 = set_hooked_point(vertex_list, temp, ptr, 1);
            ptr->p3 = set_hooked_point(vertex_list, temp, ptr, 2);
            ptr->next = root;
            root = ptr;
        }
    }
    return root;
}

float** set_hooked_point (linked_vertex *vl, char **t, quad_list *ptr, int i)
{
    linked_vertex *hook = hook_vertex(vl, my_getnbr2(t[i]));
    float **zoom = multiply1(x_rotation(1.57), zoom_matrix(15), 3, 3), **mx = 0;
    sfVertexArray_getVertex(ptr->array, i)->color = sfRed;
    (i == 0) ? ptr->p1[0][0] = hook->x : 0;
    (i == 0) ? ptr->p1[1][0] = hook->y : 0;
    (i == 0) ? ptr->p1[2][0] = hook->z : 0;
    (i == 0) ? mx = multiply1(zoom, ptr->p1, 3, 1) : 0;
    (i == 0) ? free(ptr->p1) : 0;
    (i == 1) ? ptr->p2[0][0] = hook->x : 0;
    (i == 1) ? ptr->p2[1][0] = hook->y : 0;
    (i == 1) ? ptr->p2[2][0] = hook->z : 0;
    (i == 1) ? mx = multiply1(zoom, ptr->p2, 3, 1) : 0;
    (i == 1) ? free(ptr->p2) : 0;
    (i == 2) ? ptr->p3[0][0] = hook->x : 0;
    (i == 2) ? ptr->p3[1][0] = hook->y : 0;
    (i == 2) ? ptr->p3[2][0] = hook->z : 0;
    (i == 2) ? mx = multiply1(zoom, ptr->p3, 3, 1) : 0;
    (i == 2) ? free(ptr->p3) : 0;
    return mx;
}
