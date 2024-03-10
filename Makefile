NAME	= cub3D
CC		= cc
CFLAGS	= #-Wall -Wextra -Werror
LDLIBS	= -Llibft -lft
LDMLX	= -Lmlx -lmlx -framework OpenGL -framework AppKit

SOURCES =	srcs/main.c \
			srcs/parse.c

OBJECTS	= $(SOURCES:.c=.o)

LIBFT_DIR = ./libft
MLX_DIR = ./mlx
all : $(NAME)

$(NAME) : $(OBJECTS)
	$(MAKE) -C $(LIBFT_DIR)
	$(MAKE) -C $(MLX_DIR)
	$(CC) $(CFLAGS) $(LDLIBS) $(LDMLX) $(OBJECTS) -o $(NAME)
	@echo "Setting dynamic library path for libmlx.dylib..."
	@install_name_tool -change libmlx.dylib $(MLX_DIR)/libmlx.dylib $(NAME)

clean :
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean
	rm -f $(OBJECTS)

fclean : clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re :
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re
