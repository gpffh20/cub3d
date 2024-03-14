#include "../../include/cub3D.h"

void	fill_map(char *line, t_game_info *game)
{
	int i;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (line[i] == '1' || line[i] == '0')
	{
		game->map_start++;
		if (game->map_start - 1 == 0)
			check_map_valid(line, game, SIDE);
		else if (game->map_start - 1 == game->map_height - 1)
			check_map_valid(line, game, SIDE);
		else
			check_map_valid(line, game, MIDDLE);
	}
}