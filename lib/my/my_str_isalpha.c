/*
** EPITECH PROJECT, 2021
** my_str_isalpha
** File description:
** is alpha
*/

#include "my.h"

int char_is_alpha (char c)
{
    int i = 0;
    int j = 0;

    if (c <= 90 && c >= 65)
        return (1);
    if (c <= 122 && c >= 97)
        return (1);
    return (0);
}

int my_str_isalpha (char const *str)
{
    int i = 0;
    int j = 0;

    if (str [0] == '\0')
        return (1);
    while (str [i] != '\0') {
        j = char_is_alpha (str[i]);
        if (j != 1) {
            return (0);
        }
        i = i + 1;
    }
    return (1);
}
