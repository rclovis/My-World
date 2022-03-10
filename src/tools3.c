/*
** EPITECH PROJECT, 2022
** tools3
** File description:
** tools3
*/

#include "../inc/my_world.h"

char **file_str (char *file_name)
{
    int size = 0, h = 0, return_val = 0;
    size_t len = 0;
    FILE *f = fopen(file_name, "r");
    word *root = malloc(sizeof(word)), *p = root, *p1 = root, *temp = root;
    while (return_val != -1) {
        p->str = NULL;
        return_val = getline(&(p->str), &len, f);
        if (return_val != -1) {
            p->next = malloc(sizeof(word));
            temp = p;
            p = p->next;
            p->next = NULL;
            h++;
        }
    }
    temp->next = NULL;
    char **result = malloc(sizeof(char *) * (h + 1));
    for (int i = 0;p1 != NULL;result[i] = p1->str, p1 = p1->next, i++);
    result[h] = NULL;
    return (result);
}
