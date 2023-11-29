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
    #include <sys/types.h>
    #include <dirent.h>
    #include "my.h"

    #define BACKSPACE 8
    #define ENTER 13
    #define INPUT_BUFFER_SIZE 20
    #define M_COORDS 4
    #define M_INPUT 3
    #define M_MAIN 1
    #define M_PAUSE 2

typedef struct callstack {
    int data;
    struct callstack *next;
    struct callstack *prev;
} callstack_t;

typedef struct button {
    sfFloatRect collision_box;
    sfTexture *texture;
    sfSprite *sprite;
    sfIntRect rect;
    sfText *text;
} button_t;

typedef struct menu {
    button_t **buttons;
    sfFont *font;
} menu_t;

typedef struct fps {
    sfClock *clock;
    sfFont *font;
    sfText *text;
    char buffer[10];
    int frames;
} fps_t;

typedef struct toolbar {
    sfSprite *sprite;
    sfSprite **icons;
    sfFloatRect *icons_rect;
    button_t *brush;
    int edit_mode;
    int nb_icons;
    int view_toggle;
} toolbar_t;

typedef struct global {
    callstack_t *curr_menu;
    char *name;
    fps_t *fps;
    int apply_mode;
    int complete2;
    int complete;
    int cursor;
    int edit_mode;
    int id_menu;
    int input_buffer[INPUT_BUFFER_SIZE];
    int is_typing;
    int load;
    int refresh;
    int state;
    int toggle;
    float x;
    float y;
    float x2;
    float zoom;
    int v;
    float z;
    menu_t *coords_menu;
    menu_t *input_menu;
    menu_t *main_menu;
    menu_t *pause_menu;
    quad_list *root;
    sfFont *pixel_font;
    sfMusic *click;
    sfTexture *button_texture;
    sfVertexArray *bevel;
    sfVertexArray *tile;
    toolbar_t *tb;
    sfCircleShape *vertex;
} global_t;

typedef struct linked_vertex {
    float x;
    float y;
    float z;
    struct linked_vertex *next;
} linked_vertex_t;

quad_list *spinning_clock(sfClock *c, sfRenderWindow *w, quad_list *root,
global_t *g);
button_t *button_init(const char *text, sfFont *font, sfTexture *texture);
callstack_t *callstack_add(callstack_t *curr_head, int value);
callstack_t *callstack_del(callstack_t *curr_head);
callstack_t *callstack_init(void);
char **file_str (char *file_name);
char **my_2d_array_str_split(const char *str, char sep);
char *float_to_str (double nbr);
float **multiply1 (float **m1, float **m2, int ligne_m1, int col_m2);
float **point_matrix (float x, float y, float z);
float **position_matrix (float x, float z, float zoom);
float **projection_matrix (void);
float **x_rotation (float r);
float **zoom_matrix (float zoom);
float multiply2 (float **m1, float **m2, int x, int y);
// float atof (char *str);
float ** set_hooked_point (linked_vertex_t *vl, char **t, quad_list *ptr, int i);
fps_t *fps_init(void);
global_t *setup_global (char *name, quad_list *root, int bool);
int approximation (int i, int j, int delta);
int clic_management (sfEvent *event, quad_list *root, sfRenderWindow *window,
global_t *g);
int coding_style2 (sfVector2f v1, sfVector2f v2, sfVertexArray *bevel);
int compute_centre (float **mx, quad_list *elem);
int free_quad_list (quad_list *root);
int get_item_end(const char *str, char sep);
int is_between (sfVector2f p1, sfVector2f p2, sfVector2i m);
int is_in_screen (float **v1, float **v2, float **v3, quad_list *elem);
int is_in_triangle (sfVector2i pt, sfVector2f v1, sfVector2f v2,
sfVector2f v3);
int my_item_count(const char *str, char sep);
int my_world (sfRenderWindow *window, char *f, quad_list *r, int bool);
int play_music (sfMusic *music);
int raise_line_bis (quad_list *root, sfVector2i m, sfVector2i bs,
sfVector2f *p);
int save_file (quad_list *root, char *name);
int save_points (quad_list *ptr, FILE *stream);
linked_vertex_t *get_vertex (char **object, sfVector3f pos);
linked_vertex_t *hook_vertex (linked_vertex_t *root, int i);
long long my_getnbr2 (const char *str);
menu_t * get_curr_menu(global_t *g);
menu_t *coords_menu_init(sfFont *font, sfTexture *button_texture);
menu_t *input_menu_init(sfFont *font, sfTexture *button_texture);
menu_t *main_menu_init(sfFont *font, sfTexture *button_texture);
menu_t *pause_menu_init(sfFont *font, sfTexture *button_texture);
quad_list *add_object (quad_list *root, char *file, sfVector3f pos);
quad_list *create_mesh (int x, int y, sfVector3f pos, quad_list *root);
quad_list *load_file (quad_list *root, char *file);
quad_list *tri_one (float x, float y, float z, sfTexture *texture);
quad_list *tri_two (float x, float y, float z, sfTexture *texture);
sfRenderStates *render_setup (sfTexture *texture);
sfRenderWindow *spinning_menu (int v, char **file, quad_list **root);
toolbar_t *setup_toolbar(void);
void activate_typing(global_t *g);
void calcul_projection (quad_list *elem, float **m1, float **comb);
void change_texture (quad_list *root, sfVector2i m, int button);
void coords_menu_button_on_click(global_t *g, sfEvent *evt, sfRenderWindow* w);
void currently_typing(global_t *g, sfEvent *evt);
void display_fps(fps_t *fps);
void event_poll (sfEvent event, global_t *g, quad_list *root,
sfRenderWindow *window);
void free_matrix (float **m, int y);
void input_menu_button_on_click(global_t *g, sfEvent *evt);
void loop_button (int *button, int *n_texture);
void main_menu_button_on_click(global_t *g, sfEvent *evt);
void menu_button_hover(global_t *g, sfEvent *evt);
void menu_evt(global_t *g, sfEvent *evt, sfRenderWindow *window);
void move_toolbar_cursor(toolbar_t *tb, int new_mode);
void pause_menu_button_on_click(global_t *g, sfEvent *evt);
void place_circle (quad_list *root, sfVector2i m, sfCircleShape *c);
void place_line (quad_list *root, sfVector2i m, sfVertexArray *bevel);
void place_tile (quad_list *root, sfVector2i m, sfVertexArray *tile);
void raise_line (quad_list *root, sfVector2i m, int button, float strengh);
void raise_tile (quad_list *root, sfVector2i m, int button, float strengh);
void raise_vertex (quad_list *root, sfVector2i m, int button, float strengh);
void raise_zone (quad_list *root, sfVector2i m, int button, float strengh);
void render_menu(sfRenderWindow *win, global_t *g);
void render_toolbar(sfRenderWindow *win, toolbar_t *tb);
void setup_global2 (global_t *g, int bool);
void setup_global3 (global_t *g);
void toggle_toolbar_visibility(toolbar_t *tb);
void update_mesh (quad_list *root, float zoom, float x, float z);
void aled (global_t *g, char **file, quad_list **to_send);
global_t *aled2 (global_t *g, sfClock *clock, sfEvent *event, sfRenderWindow *w);
void aled3 (global_t *g, sfRenderWindow *w);
global_t *aled4 (global_t *g, float *zoom, float *z, sfEvent *event);
quad_list *in_spin_time(sfRenderWindow *w, quad_list *r, global_t *g,
sfClock *c);
void spinning_evt(sfRenderWindow *w, sfEvent *evt, global_t *g);
sfRenderWindow *win_init(void);

#endif
