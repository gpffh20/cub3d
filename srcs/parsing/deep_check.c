#include "../../include/cub3D.h"

void	deep_check(t_game_info *game, char *line, int i)
{
	if (line[i] != '0' && line[i] != 'N' && line[i] != 'S' && line[i] != 'W'
		&& line[i] != 'E')
		return ;
	if (line[0] != '1' && line[0] != ' ')
		error_exit("Error: Invalid map.\n");
	if (game->map[game->map_start - 2][i] == ' ' || line[i - 1] == ' ')
		error_exit("Error: Invalid map.\n");
}
