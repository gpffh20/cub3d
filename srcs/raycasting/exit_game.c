#include "../../include/cub3D.h"

int	exit_game(t_game_info *game)
{
	mlx_destroy_window(game->mlx, game->win);
	exit(0);
}
