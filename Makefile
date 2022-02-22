##
## EPITECH PROJECT, 2022
## my_world
## File description:
## Makefile
##

CC	=	gcc

CFLAGS	=	-g3 -O3 -Iinc

LINKER	=	-Llib -lmy -lm \
			-lcsfml-graphics -lcsfml-window -lcsfml-audio -lcsfml-system

SRC_DIR	=	src

OBJ_DIR	=	obj

SRC	=	$(wildcard src/*.c)

OBJ	=	$(patsubst src/%.c, obj/%.o, $(SRC))

NAME	=	my_world

GREEN		=	\033[1;32m

RED			=	\033[1;31m

CYAN		=	\033[1;36m

YELLOW		=	\033[0;33m

NC			=	\033[0;0m

.PHONY:all
all:
	@make -C ./lib/my/ -s
	@make $(NAME) -s

$(NAME):	$(OBJ)
	@$(CC) $(CFLAGS) -o $@ $(OBJ) $(LINKER)
	@echo -e "[$(RED)Compiled$(NC)] \"$(YELLOW)$@$(NC)\" executable created"

$(OBJ): obj/%.o : src/%.c | obj
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo -e "[$(GREEN)Compiled$(NC)] \"$(YELLOW)$<$(NC)\" object created"

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@echo -e "[$(CYAN)Cleaning$(NC)] removed objects"

fclean:	clean
	@rm -rf $(NAME)
	@echo -e "[$(CYAN)Cleaning$(NC)] removed target"

re: fclean all