#include "../../include/cub3D.h"

void	reverse_map(t_game_info *game)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = game->map_height - 1;
	while (i < j)
	{
		temp = game->map[i];
		game->map[i] = game->map[j];
		game->map[j] = temp;
		i++;
		j--;
	}
	game->ray.player.y = game->map_height - game->ray.player.y;
}


void	get_map(char *map_file, t_game_info *game)
{
	int		fd;
	char	*line;

	if (game->player_cnt != 1)
		error_exit("Error: Invalid player.\n");
	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		error_exit("Error: Cannot open map.\n");
	game->map = init_map(game);
	game->map_start = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		fill_map(line, game);
		free(line);
		line = get_next_line(fd);
	}
	reverse_map(game);
	close(fd);
}
