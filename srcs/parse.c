#include "../include/cub3D.h"

void	error_exit(char *str)
{
	ft_putstr_fd(str, 2);
	exit(1);
}

void ft_free(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	get_color(char type, char *line, t_game_info *game)
{
	int r;
	int g;
	int b;
	char **color_info;

	color_info = ft_split(line, ',');
	r = ft_atoi(color_info[0]);
	g = ft_atoi(color_info[1]);
	b = ft_atoi(color_info[2]);
	ft_free(color_info);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		error_exit("Error: Invalid Color.\n");
	if (type == 'C' && game->ceiling_color == -1)
		game->ceiling_color = (r << 16) + (g << 8) + b;
	else if (type == 'F' && game->floor_color == -1)
		game->floor_color = (r << 16) + (g << 8) + b;
	else
		error_exit("Error: Duplicate color.\n");
}

void	get_path(char type, char *line, t_game_info *game)
{
	if (type == 'N' && game->no_path == NULL)
			game->no_path = ft_strdup(line + 3);
	else if (type == 'S' && game->so_path == NULL)
			game->so_path = ft_strdup(line + 3);
	else if (type == 'W' && game->we_path == NULL)
			game->we_path = ft_strdup(line + 3);
	else if (type == 'E' && game->ea_path == NULL)
			game->ea_path = ft_strdup(line + 3);
	else
		error_exit("Error: Duplicate path.\n");
}

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

void check_map(char *line, t_game_info *game)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != '0' && !ft_isspace(line[i]))
		{
			if ((line[i] == 'N' || line[i] == 'S' || line[i] == 'W' || line[i] == 'E') && game->player_cnt == 0)
				game->player_cnt++;
			else
				error_exit("Error: Invalid map.\n");
		}
		i++;
	}

}

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

void check_line(char *line, t_game_info *game)
{
//	int i;

	if (!ft_strncmp("NO ", line, 3) || !ft_strncmp("SO ", line, 3) ||
		!ft_strncmp("WE ", line, 3) || !ft_strncmp("EA ", line, 3))
		get_path(line[0], line, game);
	else if (!ft_strncmp("C ", line, 2) || !ft_strncmp("F ", line, 2))
		get_color(line[0], line + 2, game);
//	i = 0;
//	while (ft_isspace(line[i]))
//		i++;
	if (game->map_start == 1 && ft_isspace(line[0]))
		error_exit("Error: Invalid map.\n");
	if (line[0] == '1' || line[0] == '0')
	{
		game->map_start = 1;
		if (!game->no_path || !game->so_path || !game->we_path || !game->ea_path || game->ceiling_color == -1 || game->floor_color == -1)
			error_exit("Error: Missing information.\n");
		check_map(line, game);
		printf("%s\n", line);
		game->map_height++;
		game->map_width = ft_max(game->map_width, ft_strlen(line));
	}
	if (game->map_height > 0 && line[0] == '\n')
		game->map_height++;
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
	close(fd);
}

char	**init_map(t_game_info *game)
{
	char	**map;
	int i;

	map = (char **)malloc(sizeof(char *) * (game->map_height + 1));
	map[game->map_height] = NULL;
	i = 0;
	while (i < game->map_height)
	{
		map[i] = (char *)malloc(sizeof(char) * (game->map_width + 1));
		ft_memset(map[i], ' ', game->map_width);
		map[i][game->map_width] = '\0';
		i++;
	}
	return (map);
}


void	fill_map(char *line, t_game_info *game, int type)
{
	int			i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (type == SIDE)
	{
		while (line[i])
		{
			if (line[i] != '1' && line[i] != ' ')
				error_exit("Error: Invalid map.\n");
		}
	}
	else if (type == MIDDLE)
	{
		while (line[i])
		{
			if (line[i] == ' ')
				game->map[game->map_height - 1][i] = '1';
			i++;
		}
	}
//	while (line[i])
//	{
//		if
//	}
}

int	find_map_start(char *line, t_game_info *game)
{
	(void)game;
	int i;

	if (line[0] != 'N' || line[0] != 'S' || line[0] != 'W' || line[0] != 'E')
		return (FAIL);
	if (line[0] != 'F' || line[0] != 'C')
		return (FAIL);
	i = 0;
	while (ft_isspace(line[i]))
		i++;
//	if (line[0] == '\n')
//		// width 만큼 공백으로 채우기
//		;
//	else
//	{
//		i = 0;
//		ft_strlcpy(game->map[i], line, game->map_width + 1);
//	}
	if (line[i] == '1' || line[i] == '0')
	{
		printf("%s\n", line);


//		if (!game->no_path || !game->so_path || !game->we_path || !game->ea_path || game->ceiling_color == -1 || game->floor_color == -1)
//			error_exit("Error: Missing information.\n");
//		check_map(line, game);
//		printf("%s\n", line);
//		game->map_height++;
//		game->map_width = ft_max(game->map_width, ft_strlen(line));
	}
//	if (game->map_height > 0 && line[0] == '\n')
//		game->map_height++;
	return (SUCCESS);
}

void	get_map(char *map_file, t_game_info *game)
{
	int		fd;
	char	*line;
	int		i;

	if (game->player_cnt != 1)
		error_exit("Error: Invalid player.\n");
	fd = open(map_file, O_RDONLY);
	if (fd < 0)
		error_exit("Error: Cannot open map.\n");
	game->map = init_map(game);
	line = get_next_line(fd);
	i = 0;
	while (line != NULL)
	{
		find_map_start(line, game);
		// map 시작점 찾기
		// 개행이 나오면 전체 스페이스로 교체
		i = 0;
		if (i == 0 || i == game->map_height - 1)
			fill_map(line, game, SIDE);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	// TODO: split -> map 크기에 맞게 변형 필요
//	game->map = ft_split(total_line, '\n');
//	free(total_line);
}

void	invalid_file(char *file_name)
{
	int		len;
	char	*tmp;

	len = ft_strlen(file_name);
	tmp = ft_substr(file_name, len - 4, 4);
	if (ft_strncmp(tmp, ".cub", 4) == 0)
	{
		free(tmp);
		return ;
	}
	free(tmp);
	error_exit("Error: map extension error.");
}