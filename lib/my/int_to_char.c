/*
** EPITECH PROJECT, 2021
** int_to_char
** File description:
** int_to_char
*/

#include "my.h"

char *int_to_char (int nbr)
{
    int pow = 1, i = 0, is_neg = 0;
    char *nbr_str = NULL, *temp = NULL;
    if (nbr == 0) return my_strdup("0");
    if (nbr == 1) return my_strdup("1");
    (nbr < 0) ? is_neg = 1 : 0;
    (nbr < 0) ? nbr *= -1 : 0;
    for (;nbr / pow != 0;pow *= 10, i++);
    pow /= 10;
    nbr_str = malloc(sizeof(char) * (i + 1));
    my_setmem(nbr_str, i + 1);
    for (int j = 0;pow != 0;pow /= 10, j++) {
        nbr_str[j] = (nbr / pow) + 48;
        nbr = nbr % pow;
    }
    if (is_neg == 1) {
        temp = my_strcat("-", nbr_str);
        free(nbr_str);
        return temp;
    }
    return (nbr_str);
}
