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

/*
	sprite = toolbar sprite
	icons = toolbar icons
	editmode = position of the cursor in toolbar + tells which mode is selected
	nb_icons = length in "icons"
	view_toggle = toggle var to show/hide toolbar
*/
typedef struct toolbar {
	sfSprite *sprite;
	sfSprite **icons;
	sfFloatRect *icons_rect;
	int edit_mode;
	int nb_icons;
	int view_toggle;
} toolbar_t;

/*
	sfsprite *toolbar : sprite de la barre d'outil
*/
typedef struct global global;
struct global {
    sfCircleShape *vertex;
	sfVertexArray *bevel;
	sfVertexArray *tile;
	int edit_mode;
	int toggle;
	int apply_mode;

	// toolbar
	toolbar_t *tb;
};

typedef struct linked_vertex linked_vertex;
struct linked_vertex {
	float x;
	float y;
	float z;
	linked_vertex *next;
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
void raise_vertex (quad_list *root, sfVector2i m, int button, float strengh);
void place_tile (quad_list *root, sfVector2i m, sfVertexArray *tile);
void raise_line (quad_list *root, sfVector2i m, int button, float strengh);
void raise_tile (quad_list *root, sfVector2i m, int button, float strengh);
void raise_zone (quad_list *root, sfVector2i m, int button, float strengh);
int clic_management (sfEvent *event, quad_list *root, sfRenderWindow *window, global *g);

// test import .obj
quad_list *add_object (quad_list *root, char *file, sfVector2f pos);
linked_vertex *hook_vertex (linked_vertex *root, int i);
long long my_getnbr2 (const char *str);
linked_vertex *get_vertex (char **object);
char **file_str (char *file_name);
float **zoom_matrix (float zoom);
float **x_rotation (float r);
float **c_matrix (void);
//

// Toolbar
toolbar_t *setup_toolbar(void);
void toggle_toolbar_visibility(toolbar_t *tb);
void render_toolbar(sfRenderWindow *win, toolbar_t *tb);
void move_toolbar_cursor(toolbar_t *tb, int new_mode);

#endif
