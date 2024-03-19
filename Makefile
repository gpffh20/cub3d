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
			srcs/parsing/ft_free.c \
			srcs/parsing/get_color.c \
			srcs/parsing/get_info.c \
			srcs/parsing/get_map.c \
			srcs/parsing/get_path.c \
			srcs/parsing/init_map.c	\
			srcs/parsing/invalid_file.c \
			srcs/raycasting/draw.c \
			srcs/raycasting/mlx_pixel_put_once.c \
			srcs/raycasting/paint_background.c \
			srcs/raycasting/init_vectors.c \
			srcs/raycasting/dda.c \
			srcs/raycasting/calc_wall_length.c \
			srcs/raycasting/choose_texture.c \






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
