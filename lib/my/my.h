/*
** EPITECH PROJECT, 2021
** my_h
** File description:
** prototypes libmy
*/

#ifndef MY_H
    #define MY_H
    #include <unistd.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <SFML/Audio.h>
	#include <SFML/Graphics.h>

typedef struct node node;
struct node {
    int nbr;
    node *next;
};

typedef struct word word;
struct word {
    char *str;
    word *next;
};

typedef struct quad_list quad_list;
struct quad_list {
    sfVertexArray *array;
    sfVertexArray *strip;
    float **p1;
    float **p2;
    float **p3;
    float **p4;
	int nbr;
    int n_texture;
	sfVector3f center;
	sfRenderStates *render;
	quad_list *next;
};

quad_list *rotate (quad_list *root, quad_list **ptra);
quad_list *push (quad_list *l_a, quad_list **l_b,
quad_list **ptrb, int *cat_nbr);
quad_list *full_cat (quad_list **l_a, quad_list **l_b,
quad_list **ptra, quad_list **ptrb);
quad_list *push_swap (quad_list *l);

int my_getnbr (char *str);
char *int_to_char (int nbr);

int my_put_nbr (int nb);
void my_putchar (char c);
int my_putstr (char const *str);
int my_putarray (char * const *tab);

int char_is_alpha (char c);
int my_str_isalpha (char const *str);
int char_is_num (char c);
int my_str_isnum (char const *str);

word *str_split (char *path, char *cutter);
int true_cmp (char *str1, char *str2);
int my_strncmp (char *str1, char *str2, int n);
char *my_strcat (char *s1, char const *s2);
char *my_setmem (char *str, int len);
char *my_strdup (char const *src);
char *my_revstr(char *str);

int my_strlen (char const *str);
int my_linklen (quad_list *ptr);
int my_arraylen (char **str);
int char_in_str (char *str, char c);

#endif
