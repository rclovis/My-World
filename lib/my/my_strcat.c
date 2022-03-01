/*
** EPITECH PROJECT, 2021
** my_strcat
** File description:
** str cat
*/

#include "my.h"

char *my_strcat (char *s1, char const *s2)
{
    int len1 = my_strlen(s1), len2 = my_strlen(s2);
    char *result = malloc(sizeof(char) * (len1 + len2 + 2));
    my_setmem(result, len1 + len2 + 2);
    for (int i = 0;i < len1;i++) {
        result[i] = s1[i];
    }
    for (int i = 0;i < len2;i++) {
        result[i + len1] = s2[i];
    }
    return (result);
}
