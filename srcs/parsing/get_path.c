#include "../../include/cub3D.h"

void	get_path(char type, char *line, t_game_info *game)
{
	if (type == 'N' && game->no_path == NULL)
			game->no_path = ft_strndup((line + 3), ft_strlen(line + 3) - 1);
	else if (type == 'S' && game->so_path == NULL)
			game->so_path = ft_strndup((line + 3), ft_strlen(line + 3) - 1);
	else if (type == 'W' && game->we_path == NULL)
			game->we_path = ft_strndup((line + 3), ft_strlen(line + 3) - 1);
	else if (type == 'E' && game->ea_path == NULL)
			game->ea_path = ft_strndup((line + 3), ft_strlen(line + 3) - 1);
	else
		error_exit("Error: Duplicate path.\n");
}
