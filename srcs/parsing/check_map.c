#include "../../include/cub3D.h"

void	init_north(t_game_info *game)
{
	game->view_dir.x = 0;
	game->view_dir.y = -1;
	game->plane.x = -0.66;
	game->plane.y = 0;
}

void	init_south(t_game_info *game)
{
	game->view_dir.x = 0;
	game->view_dir.y = 1;
	game->plane.x = 0.66;
	game->plane.y = 0;
}

void	init_east(t_game_info *game)
{
	game->view_dir.x = 1;
	game->view_dir.y = 0;
	game->plane.x = 0;
	game->plane.y = 0.66;
}

void	init_west(t_game_info *game)
{
	game->view_dir.x = -1;
	game->view_dir.y = 0;
	game->plane.x = 0;
	game->plane.y = 0.66;
}

void init_ray_dir(t_game_info *game, char start_dir)
{
	if (start_dir == 'N')
		init_south(game);
	else if (start_dir == 'S')
		init_north(game);
	else if (start_dir == 'W')
		init_west(game);
	else if (start_dir == 'E')
		init_east(game);
}

void check_map(char *line, t_game_info *game)
{
	int i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != '0' && !ft_isspace(line[i]) && line[i] !='\n')
		{
			if ((line[i] == 'N' || line[i] == 'S' || line[i] == 'W' || line[i] == 'E') && game->player_cnt == 0)
			{
				game->player_cnt++;
				game->ray.player.x = i + 0.5; // player 좌표 초기화 하면서 격자점으로 옮기기
				game->ray.player.y = game->map_height + 0.5;
			}
			else
				error_exit("Error: Invalid map.\n");
		}
		i++;
	}
}
