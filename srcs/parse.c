#include "../include/cub3D.h"

void	error_exit(char *str)
{
	ft_putstr_fd(str, 2);
//	perror(str);
	exit(1);
}

void	get_color(int type, char *line, t_game_info *game)
{
	int r;
	int g;
	int b;
	char **color_info;

	color_info = ft_split(line, ',');
	r = ft_atoi(color_info[0]);
	g = ft_atoi(color_info[1]);
	b = ft_atoi(color_info[2]);
	free(color_info);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		error_exit("Error: Invalid Color.\n");
	if (type == CEILING)
	// 이거 나중에 확인해보기
		game->ceiling_color = (r << 16) + (g << 8) + b;
	else if (type == FLOOR)
		game->floor_color = (r << 16) + (g << 8) + b;
	else
		error_exit("Error: Invalid Color Type.\n");
}

int	get_path(char *line, t_game_info *game)
{
	if (ft_strncmp(line, "NO", 2) == 0 && game->no_path == NULL)
			game->no_path = ft_strdup(line + 3);
	else if (ft_strncmp(line, "SO", 2) == 0 && game->so_path == NULL)
			game->so_path = ft_strdup(line + 3);
	else if (ft_strncmp(line, "WE", 2) == 0 && game->we_path == NULL)
			game->we_path = ft_strdup(line + 3);
	else if (ft_strncmp(line, "EA", 2) == 0 && game->ea_path == NULL)
			game->ea_path = ft_strdup(line + 3);
	else if (ft_strncmp(line, "C", 1) == 0 && game->ceiling_color == NULL)
		get_color(CEILING, line + 2, game);
	else if (ft_strncmp(line, "F", 1) == 0 && game->floor_color == NULL)
		get_color(FLOOR, line + 2, game);
	else
		return (FAIL);
	return (SUCCESS);
}

void	invalid_file(char *file_name)
{
	int		len;
	char	*tmp;

	len = ft_strlen(file_name);
	tmp = ft_substr(file_name, len - 4, 4);
	if (ft_strncmp(tmp, ".fdf", 4))
	{
		free(tmp);
		return ;
	}
	free(tmp);
	error_exit("Error: map extension error.");
}

void	get_map(char *map_file, t_game_info *game)
{
	int		fd;
	char	*line;
	char	*tmp;
	char	*total_line;
	char	**map;
	int	idx;

	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		error_exit("Error: Cannot Open Map.\n");
	line = get_next_line(fd);
	total_line = ft_strdup("");
	while (line != NULL)
	{
		if (ft_strncmp(line, "\n", 1))
			continue ;
		idx = 0;
		// tmp = total_line;
		// total_line = ft_strjoin(total_line, line);
		// free(tmp);
		// free(line);
		// line = get_next_line(fd);
	}
	close(fd);
	map = ft_split(total_line, '\n');
	free(total_line);
	game->map = map;
}
