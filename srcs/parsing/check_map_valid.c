#include "../../include/cub3D.h"

void	check_map_valid(char *line, t_game_info *game, int type)
{
	int			i;

	i = 0;
	if (type == SIDE)
	{
		while (line[i])
		{
			if (line[i] != '1' && line[i] != ' ' && line[i] != '\n')
				error_exit("Error: Invalid map.\n");
			game->map[game->map_start - 1][i] = line[i];
			i++;
		}
		while (i < game->map_width)
		{
			game->map[game->map_start - 1][i] = ' ';
			i++;
		}
	}
	else if (type == MIDDLE)
	{
		while (line[i])
		{
			deep_check(game, line, i);
			game->map[game->map_start - 1][i] = line[i];
			i++;
		}
		while (i < game->map_width)
		{
			game->map[game->map_start - 1][i] = ' ';
			i++;
		}
	}
}