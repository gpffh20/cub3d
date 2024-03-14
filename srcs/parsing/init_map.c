#include "../../include/cub3D.h"

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