#ifndef CUB3D_H
# define CUB3D_H

# define FAIL -1
# define SUCCESS 0

# define CEILING 1
# define FLOOR 2

# include <stdlib.h>
# include <fcntl.h>

// test header
# include <stdio.h>
typedef struct s_game_info
{
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	int		*floor_color;
	int		*ceiling_color;
	int		start_x;
	int		start_y;
	char	**map;
	// char	*sprite_texture;
}				t_game_info;

int		error_exit(char *str);
void	invalid_file(char *file_name);



#endif
