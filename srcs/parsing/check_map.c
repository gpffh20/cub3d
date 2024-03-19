#include "../../include/cub3D.h"

void check_map(char *line, t_game_info *game)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != '0' && !ft_isspace(line[i]) && line[i] !='\n')
		{
			if ((line[i] == 'N' || line[i] == 'S' || line[i] == 'W' || line[i] == 'E') && game->player_cnt == 0)
			{
				game->player_cnt++;
				game->ray.player.x = i + 0.5;
				game->ray.player.y = game->map_height + 0.5;
			}
			else
				error_exit("Error: Invalid map.\n");
		}
		i++;
	}
}
