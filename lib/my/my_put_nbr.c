/*
** EPITECH PROJECT, 2021
** my_put_nbr.c
** File description:
** put_nbr
*/

#include "my.h"

int my_put_nbr (int nb)
{
    int pow = 1;
    if (nb < 0) {
        my_putchar('-');
        nb = nb * -1;
    }
    if (nb == 0) {
        my_putchar ('0');
        return (0);
    }
    while (nb / (pow * 10) != 0)
        pow = pow * 10;
    for (pow;pow - 1 >= 0;pow = pow / 10) {
        my_putchar (48 + (nb / pow));
        nb = nb - ((nb / pow) * pow);
    }
    return (0);
}
