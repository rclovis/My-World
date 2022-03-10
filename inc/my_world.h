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
	clock = fps own clock, reset every 1 second
	font = font used for display
	text = text used for display
	frames = number of frames ellapsed
	buffer = retrieve string equivalent of 'frames'
*/
typedef struct fps {
	sfClock *clock;
	sfFont *font;
	sfText *text;
	char buffer[10];
	int frames;
} fps_t;

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
	int refresh;
	int state;

	// toolbar
	toolbar_t *tb;

	// fps
	fps_t *fps;
};

typedef struct linked_vertex linked_vertex;
struct linked_vertex {
	float x;
	float y;
	float z;
	linked_vertex *next;
};

int my_world (int argc, char **argv, sfRenderWindow *window);
void event_poll (sfEvent event, global *g, quad_list *root, sfRenderWindow *window);
global *setup_global (void);
int clic_management (sfEvent *event, quad_list *root, sfRenderWindow *window, global *g);
int is_in_screen (float **v1, float **v2, float **v3, quad_list *elem);
sfRenderWindow *spinning_menu (int v);

//create mesh
quad_list *create_mesh (int x, int y, sfVector3f pos, quad_list *root);
quad_list *tri_one (float x, float y, float z, sfTexture *texture);
quad_list *tri_two (float x, float y, float z, sfTexture *texture);
float **point_matrix (float x, float y, float z);
//

//tools
float my_atof (char *str);
int approximation (int i, int j, int delta);
void free_matrix (float **m, int y);
int free_quad_list (quad_list *root);
int my_item_count(const char *str, char sep);
int get_item_end(const char *str, char sep);
char **my_2d_array_str_split(const char *str, char sep);
char **file_str (char *file_name);
//

//vertex computation
void calcul_projection (quad_list *elem, float **m1, float **comb);
void update_mesh (quad_list *root, float zoom, float x, float z);
//

//transformation matrix
float **zoom_matrix (float zoom);
float **x_rotation (float r);
float **position_matrix (float x, float z, float zoom);
float **projection_matrix (void);
int compute_centre (float **mx, quad_list *elem);
//

//hoover
int is_between (sfVector2f p1, sfVector2f p2, sfVector2i m);
int is_in_triangle (sfVector2i pt, sfVector2f v1, sfVector2f v2, sfVector2f v3);
void place_circle (quad_list *root, sfVector2i m, sfCircleShape *c);
void place_line (quad_list *root, sfVector2i m, sfVertexArray *bevel);
void place_tile (quad_list *root, sfVector2i m, sfVertexArray *tile);
//

//calcul matriciel
float **multiply1 (float **m1, float **m2, int ligne_m1, int col_m2);
float multiply2 (float **m1, float **m2, int x, int y);
//

//mesh tools
void raise_vertex (quad_list *root, sfVector2i m, int button, float strengh);
void raise_line (quad_list *root, sfVector2i m, int button, float strengh);
void raise_tile (quad_list *root, sfVector2i m, int button, float strengh);
void raise_zone (quad_list *root, sfVector2i m, int button, float strengh);
void change_texture (quad_list *root, sfVector2i m, int button);
void loop_button (int *button, int *n_texture);
int raise_line_bis (quad_list *root, sfVector2i m, sfVector2i bs, sfVector2f *p);
//

// import .obj
quad_list *add_object (quad_list *root, char *file, sfVector3f pos);
linked_vertex *hook_vertex (linked_vertex *root, int i);
long long my_getnbr2 (const char *str);
linked_vertex *get_vertex (char **object, sfVector3f pos);
float** set_hooked_point (linked_vertex *vl, char **t, quad_list *ptr, int i);
//

//save & load files
char *float_to_str (double nbr);
quad_list *loat_file (quad_list *root, char *file);
int save_file (quad_list *root, char *name);
int save_points (quad_list *ptr, FILE *stream);
//

// Toolbar
toolbar_t *setup_toolbar(void);
void toggle_toolbar_visibility(toolbar_t *tb);
void render_toolbar(sfRenderWindow *win, toolbar_t *tb);
void move_toolbar_cursor(toolbar_t *tb, int new_mode);
//

// FPS
void display_fps(fps_t *fps);
fps_t *fps_init(void);
//

#endif
