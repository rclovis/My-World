/*
** EPITECH PROJECT, 2022
** tools2
** File description:
** tools2
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

char *my_strndup(const char *src, size_t n)
{
    if (src == NULL)
        return NULL;
    char *dest = malloc(sizeof(char) * (n + 1));
    my_strncpy(dest, src, n);
    return dest;
}
