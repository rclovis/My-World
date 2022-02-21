/*
** EPITECH PROJECT, 2021
** nbrcmp
** File description:
** ok
*/

#include "my.h"

int true_cmp (char *str1, char *str2)
{
    if (str1[0] != str2[0])
        return (1);
    for (int i = 1;str1[i - 1] != '\0';i++) {
        if (str1[i] != str2[i])
            return (1);
    }
    return (0);
}
