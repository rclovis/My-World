/*
** EPITECH PROJECT, 2021
** my_revstr
** File description:
** rev stre
*/

#include "my.h"

char *my_revstr(char *str)
{
    char c;
    int i = 0;
    int j = 0;

    while (str [i] != '\0') {
        i = i + 1;
    }
    i = i - 1;
    while (i > j) {
        c = str [j];
        str [j] = str [i];
        str [i] = c;
        i = i - 1;
        j = j + 1;
    }
    return (str);
}
