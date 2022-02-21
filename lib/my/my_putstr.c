/*
** EPITECH PROJECT, 2021
** my_putstr
** File description:
** put string
*/

#include "my.h"

int my_putstr (char const *str)
{
    (str != NULL) ? write(1, str, my_strlen(str)) : 0;
    return (0);
}
