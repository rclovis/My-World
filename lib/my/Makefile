##
## EPITECH PROJECT, 2021
## Makefile
## File description:
## Makefile
##

SRC	=	$(wildcard *.c)

OBJ	=	$(SRC:.c=.o)

NAME	=	libmy.a

MY_H	=	my.h

all:	$(NAME)
	cp $(MY_H) ../../inc

$(NAME):	$(OBJ)
	ar rc $(NAME) $(OBJ)
	cp $(NAME) ../

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f libmy.a
	rm -f ../libmy.a

re:	fclean all
