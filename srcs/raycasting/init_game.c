#include "../../include/cub3D.h"

void	init_game(t_game_info *game)
{
	init_raycast(&game->ray);
	game->perp_wall_dist = 0;
	game->view_dir.x = 0;
	game->view_dir.y = 0;
	game->plane.x = 0;
	game->plane.y = 0;
	game->map = NULL;
	game->map_width = 0;
	game->map_height = 0;
	game->player_cnt = 0;
	game->map_start = 0;
	game->ceiling_color = -1;
	game->floor_color = -1;
	game->no_path = NULL;
	game->so_path = NULL;
	game->we_path = NULL;
	game->ea_path = NULL;
}
