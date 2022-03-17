/*
** EPITECH PROJECT, 2022
** B-MUL-200-MAR-2-1-myworld-erwan.gonzales
** File description:
** display_fps
*/

#include "my_world.h"

void display_fps(fps_t *fps)
{
    if (sfClock_getElapsedTime(fps->clock).microseconds > 1000000) {
        my_setmem(fps->buffer, 10);
        sprintf(fps->buffer, "%d", fps->frames);
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
