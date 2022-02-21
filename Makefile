##
## EPITECH PROJECT, 2021
## likedvis
## File description:
## Makefile
##

SRC	=	$(wildcard src/*.c)

OBJ	=	$(SRC:.c=.o)

NAME	=	likedvis

all:
	make -C lib/my
	$(MAKE)	$(NAME)

$(NAME):	$(OBJ)
	gcc -o $(NAME) $(OBJ) -Llib -lmy -g3 -O3 -lGL -lGLU -lcsfml-graphics	\
	-lcsfml-window -lcsfml-system -lm -lcsfml-audio

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)
	make fclean -C	lib/my

re:	fclean all
