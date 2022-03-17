/*
** EPITECH PROJECT, 2021
** my_strncmp
** File description:
** my_strncmp
*/

#include "my.h"

int my_strncmp (char *str1, char *str2, int n)
{
    for (int i = 0;i < n;i++) {
        if (str1[i] != str2[i]) return (1);
    }
    return (0);
}
