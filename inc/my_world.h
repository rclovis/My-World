/*
** EPITECH PROJECT, 2021
** my_world
** File description:
** my_world.h
*/

#ifndef my_world_H_
    #define my_world_H_
	#include <stdio.h>
	#include <stdlib.h>
	#include <unistd.h>
	#include <math.h>
	#include <SFML/Audio.h>
	#include <SFML/Graphics.h>
	#include "my.h"

typedef struct global global;
struct global {
    sfCircleShape *vertex;
	sfVertexArray *bevel;
	sfVertexArray *tile;
	int edit_mode;
	int apply_mode;
};

int my_world(int argc, char **argv);

quad_list *create_mesh (int x, int y, sfTexture *texture);
quad_list *new_elem (float x, float y, sfTexture *texture);

global *setup_global (void);
float **view_matrix (void);

void calcul_projection (quad_list *elem, float **m1, float **comb);
void update_mesh (quad_list *root, float zoom, float x, float z);
int approximation (int i, int j, int delta);
void place_circle (quad_list *root, sfVector2i m, sfCircleShape *c);
int is_between (sfVector2f p1, sfVector2f p2, sfVector2i m);

void free_matrix (float **m, int y);
float **projection_matrix (void);
void place_line (quad_list *root, sfVector2i m, sfVertexArray *bevel);
float **position_matrix (float x, float z, float zoom);

float **multiply1 (float **m1, float **m2, int ligne_m1, int col_m2);
float multiply2 (float **m1, float **m2, int x, int y);
float **combine (float **m1, float **m2);

int is_in_triangle (sfVector2i pt, sfVector2f v1, sfVector2f v2, sfVector2f v3);
void raise_vertex (quad_list *root, sfVector2i m, int button);
void place_tile (quad_list *root, sfVector2i m, sfVertexArray *tile);
void raise_line (quad_list *root, sfVector2i m, int button);
void raise_tile (quad_list *root, sfVector2i m, int button);
int clic_management (sfEvent *event, quad_list *root, sfRenderWindow *window, global *g);

#endif
