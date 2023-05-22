# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/04 16:03:19 by marirodr          #+#    #+#              #
#    Updated: 2023/05/22 18:29:22 by marirodr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	so_long

NAME_BONUS	=	so_long_bonus

CC			=	gcc -g

CFLAGS		=	-Wall -Wextra -Werror

LIBFT		=	libft/libft.a

MLX42		=	MLX42/libmlx42.a

SRC			=	so_long.c free_n_error.c map_check.c game.c ply_moves.c \
				utils.c \

SRC_BONUS = 	bonus/so_long.c bonus/free_n_error.c bonus/map_check.c \
				bonus/game.c bonus/ply_moves.c bonus/utils.c \
			  
OBJ			=	$(SRC:.c=.o)

OBJ_BONUS	=	$(SRC_BONUS:.c=.o)

EXTRA		=	-framework Cocoa -framework OpenGL -framework IOKit -Iinclude -lglfw -L"/Users/marirodr/.brew/opt/glfw/lib/"

GREEN		=	\033[0;32m
RED			=	\033[0;31m
END			=	\033[0m

RM			=	rm -rf

all:	$(NAME)

#no podemos llamar a (LIBFT) ni (MLX42) en (NAME) porque estaria buscando los .a
#antes de crearlos y da error. Hacemos previamente las reglas para compilar tanto
#libft como MLX42	y ya luego compilamos con flags y frameworks los .a de ambas 
#librerias. 
$(NAME): $(OBJ)
					@make -s -C libft
					@make -s -C MLX42
					@$(CC) $(CFLAGS) $(OBJ) $(MLX42) $(LIBFT) $(EXTRA) -o $(NAME)
					@echo "$(GREEN)So_long ready$(END)"
				
.c.o:
					@$(CC) $(CFLAGS) -c $< -o $@

bonus: $(OBJ_BONUS)
					@make -s -C libft
					@make -s -C MLX42
					@$(CC) $(CFLAGS) $(OBJ_BONUS) $(MLX42) $(LIBFT) $(EXTRA) -o $(NAME_BONUS)
					@echo "$(GREEN)So_long bonus ready$(END)"

clean:
				@$(RM) $(OBJ) $(OBJ_BONUS)
				@echo "$(RED)Compiled objects have been removed$(END)"

fclean:	clean
				@$(RM) $(NAME) $(NAME_BONUS)
				@make fclean -C libft
				@make clean -C MLX42/
				@echo "$(RED)Executables objects have been removed$(END)"

re: fclean all

.PHONY: all, clean, fclean, re