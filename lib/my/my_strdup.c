/*
** EPITECH PROJECT, 2021
** my_strdup
** File description:
** str dup
*/

#include "my.h"
#include <stdlib.h>

char *my_strdup (char const *src)
{
    int i = 0, j = 0;
    char *strd = malloc(sizeof(char) * my_strlen(src));
    for (int k = 0;k < my_strlen(src);strd[k] = '\0', k++);
    while (src[j] != '\0') {
        strd[j] = src[j];
        j++;
    }
    strd[j] = '\0';
    return (strd);
}
