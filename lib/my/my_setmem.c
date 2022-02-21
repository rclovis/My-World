/*
** EPITECH PROJECT, 2021
** my_setmem
** File description:
** my_setmem
*/

#include "my.h"

char *my_setmem (char *str, int len)
{
    for (int i = 0;i <len;i++) {
        str[i] = '\0';
    }
    return str;
}
