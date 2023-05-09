# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marirodr <marirodr@student.42malaga.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/04 16:03:19 by marirodr          #+#    #+#              #
#    Updated: 2023/05/09 17:23:45 by marirodr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= so_long

CC			= gcc

CFLAGS	= -Wall -Wextra -Werror

LIBFT		= libft/libft.a

MLX42		= MLX42/libmlx42.a

SRC			= so_long.c \

OBJ			= $(SRC:.c=.o)

EXTRA		= -framework Cocoa -framework OpenGL -framework IOKit -Iinclude -lglfw -L"/Users/marirodr/.brew/opt/glfw/lib/"

GREEN		=		\033[0;32m
RED			=		\033[0;31m
END			=		\033[0m

RM			= rm -rf

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

clean:
				@$(RM) $(OBJ)
				@echo "$(RED)Compiled objects have been removed$(END)"

fclean:	clean
				@$(RM) $(NAME)
				@make fclean -C libft
				@make clean -C MLX42/
				@echo "$(RED)Executables objects have been removed$(END)"

re: fclean all

.PHONY: all, clean, fclean, re