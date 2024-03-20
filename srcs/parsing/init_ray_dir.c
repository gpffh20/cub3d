#include "../../include/cub3D.h"

static void	init_north(t_game_info *game)
{
	game->view_dir.x = 0;
	game->view_dir.y = 1;
	game->plane.x = 0.66;
	game->plane.y = 0;
}

static void	init_south(t_game_info *game)
{
	game->view_dir.x = 0;
	game->view_dir.y = -1;
	game->plane.x = -0.66;
	game->plane.y = 0;
}

static void	init_east(t_game_info *game)
{
	game->view_dir.x = 1;
	game->view_dir.y = 0;
	game->plane.x = 0;
	game->plane.y = 0.66;
}

static void	init_west(t_game_info *game)
{
	game->view_dir.x = -1;
	game->view_dir.y = 0;
	game->plane.x = 0;
	game->plane.y = 0.66;
}

void	init_ray_dir(t_game_info *game, char start_dir)
{
	if (start_dir == 'N')
		init_north(game);
	else if (start_dir == 'S')
		init_south(game);
	else if (start_dir == 'W')
		init_west(game);
	else if (start_dir == 'E')
		init_east(game);
}
