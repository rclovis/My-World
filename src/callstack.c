/*
** EPITECH PROJECT, 2022
** B-MUL-200-MAR-2-1-myworld-erwan.gonzales
** File description:
** callstack
*/

#include "my_world.h"

callstack_t *callstack_init(void)
{
    callstack_t *callstack_menu = malloc(sizeof(callstack_t));
    callstack_menu->data = 0;
    callstack_menu->next = NULL;
    callstack_menu->prev = NULL;
    return callstack_menu;
}

callstack_t *callstack_add(callstack_t *curr_head, int value)
{
    callstack_t *new_head = callstack_init();
    new_head->data = value;
    if (curr_head == NULL)
        return new_head;
    curr_head->next = new_head;
    new_head->prev = curr_head;
    return new_head;
}

callstack_t *callstack_del(callstack_t *curr_head)
{
    callstack_t *new_head = curr_head->prev;
    free(curr_head);
    if (new_head != NULL)
        new_head->next = NULL;
    return new_head;
}
