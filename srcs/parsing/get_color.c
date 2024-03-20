#include "../../include/cub3D.h"

static void	ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

static void	check_color(char **color_info)
{
	int	i;
	int	j;

	i = 0;
	while (color_info[i])
	{
		j = 0;
		while (color_info[i][j])
		{
			if (!ft_isdigit(color_info[i][j]))
				error_exit("Error: Invalid color.\n");
			j++;
		}
		i++;
	}
	if (i != 3)
		error_exit("Error: Invalid color.\n");
}

void	get_color(char type, char *line, t_game_info *game)
{
	int		r;
	int		g;
	int		b;
	char	**color_info;

	color_info = ft_split(line, ',');
	check_color(color_info);
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
