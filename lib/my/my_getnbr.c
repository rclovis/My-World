/*
** EPITECH PROJECT, 2021
** my_getnbr
** File description:
** getnbr
*/

#include "my.h"

int my_getnbr (char *str)
{
    long e = 1, pow = 1, result = 0, i = 0;
    if (str[0] == '-') {
        e = -1;
        str = &str[1];
    }
    i = my_strlen(str) - 1;
    for (i;i >= 0;i--) {
        result = result + (str[i] - 48) * pow;
        pow = pow * 10;
    }
    result = result * e;
    return result;
}
