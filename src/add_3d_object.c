/*
** EPITECH PROJECT, 2022
** add_3d_object
** File description:
** add_3d_object
*/

#include "../inc/my_world.h"

int get_item_end(const char *str, char sep)
{
    int i = 0;
    while (str[i] != 0 && str[i] != sep)
        i++;
    return i;
}

char *my_strncpy(char *dest, const char *src, size_t n)
{
    if (src == NULL)
        return dest = NULL;
    for (int i = 0; i < n; i++)
        dest[i] = src[i];
    dest[n] = 0;
    return dest;
}

char **my_2d_array_str_split(const char *str, char sep)
{
    int nb_item = my_item_count(str, sep), in_item = 0;
    char **array = malloc(sizeof(char *) * (nb_item + 1));
    for (int i = 0; *str != 0; str++) {
        if (*str != sep && in_item == 0) {
            array[i] = my_strndup(str, get_item_end(str, sep));
            in_item = 1;
            i++;
        } else if (*str == sep)
            in_item = 0;
    }
    array[nb_item] = NULL;
    return array;
}

int my_item_count(const char *str, char sep)
{
    int in_item = 0, item_count = 0;
    while (*str != 0) {
        if (*str != sep && in_item == 0) {
            item_count++;
            in_item = 1;
        }
        else if (*str == sep)
            in_item = 0;
        str++;
    }
    return item_count;
}

char **file_str (char *file_name)
{
    int size = 0, h = 0, return_val = 0;
    size_t len = 0;
    FILE *f = fopen(file_name, "r");
    word *root = malloc(sizeof(word)), *p = root, *temp = root;
    char **result = NULL;
    while (return_val != -1) {
        p->str = NULL;
        return_val = getline(&(p->str), &len, f);
        if (return_val != -1) {
            p->next = malloc(sizeof(word));
            temp = p;
            p = p->next;
            p->next = NULL;
            h++;
        }
    }

    temp->next = NULL;
    p = root;
    result = malloc(sizeof(char *) * (h + 1));
    for (int i = 0;p != NULL;p = p->next, i++)
        result[i] = p->str;
    result[h] = NULL;
    return (result);
}

linked_vertex *get_vertex (char **object)
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
            ptr->x = atof(temp[0]);
            ptr->y = atof(temp[1]);
            ptr->z = atof(temp[2]);
            free(temp[0]);
            free(temp[1]);
            free(temp[2]);
            free(temp);
        }
    }
    return (root->next);
}

char *my_strndup(const char *src, size_t n)
{
    if (src == NULL)
        return NULL;
    char *dest = malloc(sizeof(char) * (n + 1));
    my_strncpy(dest, src, n);
    return dest;
}

long long my_getnbr2(const char *str)
{
    if (str == NULL)
        return 0;
    int sign = 1, nbr_len = 0;
    long long nbr = 0;
    while ((*str == '-' || *str == '+')) {
        if (*str == '-')
            sign *= -1;
        str++;
    }
    for (nbr_len = 0; char_is_num(str[nbr_len]); nbr_len++);
    if (nbr_len == 0)
        return 0;
    int exp = pow(10, nbr_len-1);
    while (char_is_num(*str)) {
        nbr += (*str - '0') * exp;
        exp /= 10;
        str++;
    }
    return nbr * sign;
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
    char **object = file_str(file);
    quad_list *ptr = NULL;
    sfTexture *yes = sfTexture_createFromFile("assets/textures/textures.png", NULL);
    char **temp = NULL;
    float **zoom = multiply1(x_rotation(1.57), zoom_matrix(15), 3, 3);
    float **temp4 = NULL;
    linked_vertex *vertex_list = get_vertex(object), *hook = NULL;
    for (int i = 0;object[i] != NULL;i++) {
        if (object[i][0] == 'f') {
            temp = my_2d_array_str_split(&object[i][2], ' ');
            // ptr = new_elem(0, 0, NULL, (sfVector3f) {0, 0, 0});
            ptr = tri_one(0, 0, 0, NULL);

            sfVertexArray_getVertex(ptr->array, 0)->color = sfRed;
            sfVertexArray_getVertex(ptr->array, 1)->color = sfRed;
            sfVertexArray_getVertex(ptr->array, 2)->color = sfRed;

            hook = hook_vertex(vertex_list, my_getnbr2(temp[0]));
            ptr->p1[0][0] = hook->x + pos.x;
            ptr->p1[1][0] = hook->y + pos.z;
            ptr->p1[2][0] = hook->z + pos.y;

            temp4 = multiply1(zoom, ptr->p1, 3, 1);
            free(ptr->p1);
            ptr->p1 = temp4;

            hook = hook_vertex(vertex_list, my_getnbr2(temp[1]));
            ptr->p2[0][0] = hook->x + pos.x;
            ptr->p2[1][0] = hook->y + pos.z;
            ptr->p2[2][0] = hook->z + pos.y;

            temp4 = multiply1(zoom, ptr->p2, 3, 1);
            free(ptr->p2);
            ptr->p2 = temp4;

            hook = hook_vertex(vertex_list, my_getnbr2(temp[2]));
            ptr->p3[0][0] = hook->x + pos.x;
            ptr->p3[1][0] = hook->y + pos.z;
            ptr->p3[2][0] = hook->z + pos.y;

            temp4 = multiply1(zoom, ptr->p3, 3, 1);
            free(ptr->p3);
            ptr->p3 = temp4;

            ptr->next = root;
            root = ptr;
        }
    }
    return root;
}
