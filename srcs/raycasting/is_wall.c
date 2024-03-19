#include "../../include/cub3D.h"

int is_wall(t_game_info *game, int x, int y)
{
	if (x < 1 || y < 1 || x > game->map_width - 1 || y > game->map_height - 1)
		return (TRUE);
	if (game->map[y][(int)game->ray.player.x] == '0' &&
		game->map[(int)game->ray.player.y][x] == '0')
		return (FALSE);
	return (TRUE);
}
