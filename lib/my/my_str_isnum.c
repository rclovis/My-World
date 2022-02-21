/*
** EPITECH PROJECT, 2021
** my_str_sinum
** File description:
** is num
*/

#include "my.h"

int char_is_num (char c)
{
    int i = 0;
    int j = 0;
    if (c >= 48 && c <= 57)
        return (1);
    return (0);
}

int my_str_isnum (char const *str)
{
    int i = 0;
    int j = 0;
    if (str[0] == '\0')
        return (1);
    if (str[0] == '-')
        i = i + 1;
    while (str[i] != '\0') {
        j = char_is_num (str[i]);
        if (j != 1) {
            return (0);
        }
        i = i + 1;
    }
    return (1);
}
