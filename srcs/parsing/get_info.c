#include "../../include/cub3D.h"

static void check_xpm(t_game_info *game)
{
	int fd;

	fd = open(game->no_path, O_RDONLY);
	if (fd < 0 || close(fd) < 0)
		error_exit("Error: Invalid texture file.\n");
	fd = open(game->so_path, O_RDONLY);
	if (fd < 0 || close(fd) < 0)
		error_exit("Error: Invalid texture file.\n");
	fd = open(game->we_path, O_RDONLY);
	if (fd < 0 || close(fd) < 0)
		error_exit("Error: Invalid texture file.\n");
	fd = open(game->ea_path, O_RDONLY);
	if (fd < 0 || close(fd) < 0)
		error_exit("Error: Invalid texture file.\n");
}

void	get_info(char *map_file, t_game_info *game)
{
	int		fd;
	char	*line;

	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		error_exit("Error: Cannot open map.\n");
	line = get_next_line(fd);
	while (line != NULL)
	{
		check_line(line, game);
		free(line);
		line = get_next_line(fd);
	}
	check_xpm(game);
	close(fd);
}