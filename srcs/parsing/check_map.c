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
				game->start_x = i;
				game->start_y = game->map_height;
			}
			else
				error_exit("Error: Invalid map.\n");
		}
		i++;
	}

}