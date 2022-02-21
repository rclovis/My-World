/*
** EPITECH PROJECT, 2021
** my_show_world_array
** File description:
** shows word array
*/

#include "my.h"

int my_putarray (char * const *tab)
{
    int i = 0;
    while (tab [i] != NULL) {
        my_putstr (tab [i]);
        i = i + 1;
    }
    return (0);
}
