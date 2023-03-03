# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bsilva-c <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/06 16:02:55 by bsilva-c          #+#    #+#              #
#    Updated: 2023/01/09 16:03:52 by bsilva-c         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=cc
CFLAGS=-Wall -Werror -Wextra -O3
MLXFLAGS=-L ./minilibx-linux -lm -lmlx -Ilmlx -lXext -lX11
DEPS=fdf.h minilibx-linux/mlx.h libft/libft.a

NAME=fdf
SRC=color.c draw_utils.c exit.c main.c map.c t_mlx_init.c win_n_draw.c
OBJ=$(SRC:.c=.o)

LIBFT = libft/libft.a

all: deps $(NAME)
deps:
	@$(MAKE) -C ./libft
	@$(MAKE) -C ./minilibx-linux
$(NAME): $(OBJ) $(DEPS)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLXFLAGS) -o $(NAME)
clean:
	@$(MAKE) $@ -C ./libft
	@$(MAKE) $@ -C ./minilibx-linux
	@rm -rf $(OBJ)
fclean: clean
	@$(MAKE) $@ -C ./libft
	@rm -rf $(NAME)
re: fclean all
	@$(MAKE) $@ -C ./libft
	@$(MAKE) $@ -C ./minilibx-linux
