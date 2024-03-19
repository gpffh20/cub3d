#include "../../include/cub3D.h"

void	check_map_valid(char *line, t_game_info *game, int type)
{
	int			i;

	i = 0;
	if (type == SIDE_FIRST)
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
	else if (type == SIDE_LAST)
	{
		while (line[i])
		{
			deep_check(game, line, i);
			if (line[i] != '1' && line[i] != ' ' && line[i] != '\n')
				error_exit("Error: Invalid map.\n");
			game->map[game->map_start - 1][i] = line[i];
			if (line[i] == ' ' && game->map[game->map_start - 2][i] == '0')
				error_exit("Error: Invalid map.\n");
			i++;
		}
		while (i < game->map_width)
		{
			game->map[game->map_start - 1][i] = ' ';
			if (line[i] == ' ' && game->map[game->map_start - 2][i] == '0')
				error_exit("Error: Invalid map.\n");
			i++;
		}
	}
	else if (type == MIDDLE)
	{
		while (line[i])
		{
			deep_check(game, line, i);
			game->map[game->map_start - 1][i] = line[i];
			if (line[i] == 'N' || line[i] == 'S' || line[i] == 'W' || line[i] == 'E')
			{
				init_ray_dir(game, line[i]);
				game->map[game->map_start - 1][i] = '0';
			}
			i++;
		}
		while (i < game->map_width)
		{
			game->map[game->map_start - 1][i] = ' ';
			i++;
		}
	}
}