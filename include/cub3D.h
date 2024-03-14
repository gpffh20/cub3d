#ifndef CUB3D_H
# define CUB3D_H

# define FAIL -1
# define SUCCESS 0

# define SIDE 1
# define MIDDLE 2

# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>

# include "../libft/libft.h"
# include "../mlx/mlx.h"

typedef struct s_game_info
{
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	int		floor_color;
	int		ceiling_color;
	int		start_x;
	int		start_y;
	char	**map;
	int		map_width;
	int		map_height;
	int		player_cnt;
	int		map_start;
	// char	*sprite_texture;
}				t_game_info;

void	error_exit(char *str);
void	invalid_file(char *file_name);
void	get_info(char *map_file, t_game_info *game);
void	get_map(char *map_file, t_game_info *game);
void	check_map_valid(char *line, t_game_info *game, int type);
void	fill_map(char *line, t_game_info *game);
void	deep_check(t_game_info *game, char *line, int i);
void	check_line(char *line, t_game_info *game);
char	**init_map(t_game_info *game);
void	check_map(char *line, t_game_info *game);
void	ft_free(char **str);
void	get_color(char type, char *line, t_game_info *game);
void	get_path(char type, char *line, t_game_info *game);

#endif
