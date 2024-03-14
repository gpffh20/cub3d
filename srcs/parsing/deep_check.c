#include "../../include/cub3D.h"

void	deep_check(t_game_info *game, char *line, int i)
{
	if (line[i] != '0')
		return ;
	if (line[0] == '0')
		error_exit("Error: Invalid map.\n");
	if (line[game->map_start - 2] == ' ' || line[i-1] == ' ')
		error_exit("Error: Invalid map.\n");
}