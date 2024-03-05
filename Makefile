NAME	= cub3D
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
LDLIBS	= -Llibft -lft
LDMLX	= -Lmlx -lmlx -framework OpenGL -framework AppKit

SOURCES = srcs/main.c

OBJECTS	= $(SOURCES:.c=.o)

LIBFT_DIR = ./libft

all : $(NAME)

$(NAME) : $(OBJECTS)
	$(MAKE) -C $(LIBFT_DIR)
	$(MAKE) -C mlx
	$(CC) $(CFLAGS) $(LDLIBS) $(LDMLX) $(OBJECTS) -o $(NAME)

clean :
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C mlx clean
	rm -f $(OBJECTS)

fclean : clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re :
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re
