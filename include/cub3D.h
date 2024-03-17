#ifndef CUB3D_H
# define CUB3D_H

# define FAIL -1
# define SUCCESS 0

# define SIDE 1
# define MIDDLE 2

# define KEY_W 13
# define KEY_S 1
# define KEY_A 0
# define KEY_D 2
# define ROTATE_LEFT 123
# define ROTATE_RIGHT 124
# define ESC 53

# define DESTROY 17
# define KEY_RELEASE 3
# define KEY_PRESS 2

# define CEILING 1
# define FLOOR 2

# define SCREEN_WIDTH 1150
# define SCREEN_HEIGHT 800

# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>

# include "../libft/libft.h"
# include "../mlx_lib/mlx.h"

typedef struct s_coordinate_point_int
{
	int			x;
	int			y;
}				t_point_int;

typedef struct s_coordinate_point_double
{
	double	x;
	double	y;
}				t_point_double;

typedef struct s_texture
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		floor;
	int		ceiling;
}	t_texture;

typedef struct s_raycast
{
	t_point_double	ray_dir;
	t_point_double	side_dist;
	t_point_double	delta_dist;
	t_point_double	player; // map 좌표 double
	t_point_int			player_pos; // map section 좌표 int
	t_point_int			step_dir;
	int				side;
	int				line_height;
	int				draw_start;
	int				draw_end;
	double			hit;
}	t_raycast;

typedef struct s_game_info
{
	t_raycast	ray;
	t_texture	texture;
	t_point_double view_dir;
	t_point_double plane;
	void	*mlx;
	void	*win;
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	int		floor_color;
	int		ceiling_color;
	char	**map;
	int		map_width;
	int		map_height;
	// t_point_int	player;
	int		player_cnt;
	int		map_start;
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
void	paint_background(t_game_info *game);

void	draw_map(t_game_info *game);
void	paint_background(t_game_info *game);
void calc_ray_params(t_game_info *game, t_raycast *ray, int monitor);
void init_ray_dir(t_game_info *game, char start_dir);

#endif
