/*
** EPITECH PROJECT, 2021
** char_in_str
** File description:
** char_in_str
*/

#include "my.h"

int char_in_str (char *str, char c)
{
    for (int i = 0;str[i] != '\0';i++) {
        if (str[i] == c) {
            return 1;
        }
    }
    return 0;
}
