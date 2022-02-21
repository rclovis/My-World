/*
** EPITECH PROJECT, 2021
** my_arraylen
** File description:
** my_arraylen
*/

#include "my.h"

int my_arraylen (char **str)
{
    int i = 0;
    for (i;str[i] != NULL;i++);
    return i;
}
