/*
** EPITECH PROJECT, 2021
** operators
** File description:
** operators
*/

#include "my.h"

quad_list *rotate (quad_list *root, quad_list **ptra)
{
    quad_list *new_root = root->next;
    if (root->next == NULL)
        return root;
    root->next = NULL;
    (*ptra)->next = root;
    (*ptra) = (*ptra)->next;
    return new_root;
}

quad_list *push (quad_list *l_a, quad_list **l_b,
quad_list **ptrb, int *cat_nbr)
{
    quad_list *ptr = l_a;
    *cat_nbr = *cat_nbr + 1;
    if ((*l_b) == NULL) {
        (*l_b) = l_a;
        (*ptrb) = l_a;
        l_a = l_a->next;
        (*l_b)->next = NULL;
        cat_nbr++;
        return l_a;
    }
    l_a = l_a->next;
    ptr->next = NULL;
    (*ptrb)->next = ptr;
    (*ptrb) = (*ptrb)->next;
    return l_a;
}

quad_list *full_cat (quad_list **l_a, quad_list **l_b,
quad_list **ptra, quad_list **ptrb)
{
    if ((*l_a) != NULL) {
        (*ptra)->next = (*l_b);
        ((*ptrb) != NULL) ? (*ptra) = (*ptrb) : 0;
        (*l_b) = NULL;
        (*ptrb) = (*l_b);
    } else {
        (*l_a) = (*l_b);
        (*l_b) = NULL;
        (*ptra) = (*ptrb);
        (*ptrb) = NULL;
    }
    return NULL;
}

int my_linklen (quad_list *ptr)
{
    int i = 0;
    for (i;ptr != NULL;ptr = ptr->next, i++);
    return i;
}

quad_list *push_swap (quad_list *l)
{
    quad_list *l_b = NULL, *ptra = NULL, *ptrb = l_b;
    int len = my_linklen(l), c = 0;
    for (ptra = l;ptra->next != NULL;ptra = ptra->next);
    for (long two = 1;two < 2147483648;two *= 2) {
        for (int i = 0;i < len;i++)
            l = ((l->nbr & two) == 0) ? push(l, &l_b, &ptrb, &c) :
            rotate(l, &ptra);
        full_cat (&l, &l_b, &ptra, &ptrb);
    }
    for (int i = 0;i < len;i++)
        l = ((l->nbr & 2147483648) != 0) ? push(l, &l_b, &ptrb, &c) :
        rotate(l, &ptra);
    full_cat (&l, &l_b, &ptra, &ptrb);
    return l;
}
