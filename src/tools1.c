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

float my_atof (char *str)
{
    int i = 0;
    double p1 = 0, p2 = 0, pow = 1, sign = 1;
    for (int j = 0;str[j] != '\0';j++)
        (str[j] == '\n') ? str[j] = '\0' : 0;
    if (str[0] == '-') {
        sign = -1;
        str = &str[1];
    }
    for (i = 0;str[i] != '.' && str[i] != '\0';i++);
    str[i + 1 + 9] = '\0';
    p1 = my_getnbr2(str);
    p2 = my_getnbr2(&str[i + 1]);
    for (int j = 0;j < my_strlen(&str[i + 1]);pow /= 10, j++);
    return (p1 + (p2 * pow)) * sign;
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
