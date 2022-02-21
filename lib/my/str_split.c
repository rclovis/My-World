/*
** EPITECH PROJECT, 2021
** str_split
** File description:
** str_split
*/

#include "my.h"

word *str_split (char *path, char *cutter)
{
    int start = 0, end = 0, cnt_words = 0, k3 = 0;
    char *wrd = NULL;
    word *root = malloc(sizeof(word)), *ptr_last = root;
    root->next = NULL;
    while (path[start] != '\0') {
        for (;char_in_str(cutter, path[start]);start++, end++);
        for (;char_in_str(cutter, path[end]) == 0 && path[end] != '\0';end++);
        wrd = malloc(sizeof(char) * (end - start + 1));
        wrd[end - start] = '\0';
        for (int i = start;i < end;wrd[i - start] = path[i], i++)
        if (end != start) {
            ptr_last->next = malloc(sizeof(word));
            ptr_last = ptr_last->next;
            ptr_last->str = wrd;
            start = end;
        } else
            free(wrd);
        for (;char_in_str(cutter, path[start]);start++, end++);
    }
    return root->next;
}
