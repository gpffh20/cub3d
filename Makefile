# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gykoh <gykoh@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/20 09:20:17 by gykoh             #+#    #+#              #
#    Updated: 2024/03/20 11:17:08 by gykoh            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= cub3D
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
LDLIBS	= -Llibft -lft
LDMLX	= -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit

SOURCES =	srcs/main.c \
			srcs/parsing/check_line.c \
			srcs/parsing/check_map.c \
			srcs/parsing/check_map_valid.c \
			srcs/parsing/deep_check.c \
			srcs/parsing/error_exit.c \
			srcs/parsing/fill_map.c \
			srcs/parsing/get_color.c \
			srcs/parsing/get_info.c \
			srcs/parsing/get_map.c \
			srcs/parsing/get_path.c \
			srcs/parsing/init_map.c	\
			srcs/parsing/init_ray_dir.c \
			srcs/parsing/invalid_file.c \
			srcs/raycasting/calc_ray_params.c \
			srcs/raycasting/calc_wall_length.c \
			srcs/raycasting/choose_texture.c \
			srcs/raycasting/control_player.c \
			srcs/raycasting/dda.c \
			srcs/raycasting/draw_map.c \
			srcs/raycasting/draw_texture.c \
			srcs/raycasting/exit_game.c \
			srcs/raycasting/fetch_pixel_color.c \
			srcs/raycasting/init_game.c \
			srcs/raycasting/init_move_flag.c \
			srcs/raycasting/init_raycast.c \
			srcs/raycasting/init_mlx.c \
			srcs/raycasting/init_vectors.c \
			srcs/raycasting/is_wall.c \
			srcs/raycasting/key_press_n_release.c \
			srcs/raycasting/mlx_pixel_put_once.c \
			srcs/raycasting/move_player.c \
			srcs/raycasting/paint_background.c \
			srcs/raycasting/rotate_player.c \

OBJECTS	= $(SOURCES:.c=.o)

LIBFT_DIR = ./libft
MLX_DIR = ./mlx_lib
all : $(NAME)

$(NAME) : $(OBJECTS)
	@$(MAKE) -C $(LIBFT_DIR)
	@$(MAKE) -C $(MLX_DIR)
	@$(CC) $(CFLAGS) $(LDLIBS) $(LDMLX) $(OBJECTS) -o $(NAME)
	@install_name_tool -change libmlx.dylib $(MLX_DIR)/libmlx.dylib $(NAME)
	@echo $(YELLOW) "⚡︎	[ libft ]	Ready to run libft" $(RESET)
	@echo $(CYAN) "⚡︎	[  mlx  ]	Ready to run mlx" $(RESET)
	@echo $(GREEN) "⚡︎	[ cub3D ]	Ready to run cub3D" $(RESET)

%.o: %.c ./include/cub3D.h
	@$(CC) $(CFLAGS) -c $< -o $@

clean :
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo $(YELLOW) "⚡︎	[ libft ]	Removed Object files" $(RESET)
	@$(MAKE) -C $(MLX_DIR) clean
	@echo $(CYAN) "⚡︎	[  mlx  ]	Removed Object files" $(RESET)
	@rm -f $(OBJECTS)
	@echo $(GREEN) "⚡︎	[ cub3D ]	Removed Object files" $(RESET)

fclean : clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo $(YELLOW) "⚡︎	[ libft ]	Removed libft.a" $(RESET)
	@rm -f $(NAME)
	@echo $(GREEN) "⚡︎	[ cub3D ]	Removed cub3D" $(RESET)

re :
	@$(MAKE) fclean
	@$(MAKE) all

.PHONY: all clean fclean re

RESET	= "\x1b[0m"
GREY	= "\x1b[30m"
RED		= "\x1b[31m"
GREEN	= "\x1b[32m"
YELLOW	= "\x1b[33m"
BLUE	= "\x1b[34m"
PURPLE	= "\x1b[35m"
CYAN	= "\x1b[36m"
WHITE	= "\x1b[37m"
