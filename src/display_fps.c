/*
** EPITECH PROJECT, 2022
** B-MUL-200-MAR-2-1-myworld-erwan.gonzales
** File description:
** display_fps
*/

#include "my_world.h"

void my_sprintf(fps_t *fps)
{
    int pow = 1;
    int i = 0;
    if (fps->frames == 0) {
        fps->buffer[i] = '0';
        i++;
    }
    while (fps->frames / (pow * 10) != 0)
        pow = pow * 10;
    for (pow;pow - 1 >= 0;pow = pow / 10) {
        fps->buffer[i] = ((48 + (fps->frames / pow)));
        fps->frames = fps->frames - ((fps->frames / pow) * pow);
        i++;
    }
    fps->buffer[i] = 0;
}

void display_fps(fps_t *fps)
{
    if (sfClock_getElapsedTime(fps->clock).microseconds > 1000000) {
        my_setmem(fps->buffer, 10);
        my_sprintf(fps);
        sfText_setString(fps->text, fps->buffer);
        fps->frames = 0;
        sfClock_restart(fps->clock);
    }
}

fps_t *fps_init(void)
{
    fps_t *fps = malloc(sizeof(fps_t));
    fps->clock = sfClock_create();
    fps->font = sfFont_createFromFile("assets/fonts/bold.ttf");
    fps->text = sfText_create();
    fps->frames = 0;
    my_setmem(fps->buffer, 10);
    sfText_setFont(fps->text, fps->font);
    sfText_setPosition(fps->text, (sfVector2f) {20, 20});
    return fps;
}
