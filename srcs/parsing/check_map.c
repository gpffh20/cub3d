#include "../../include/cub3D.h"

void	init_north(t_game_info *game)
{
	game->view_dir.x = 0;
	game->view_dir.y = 1;
	game->plane.x = 0.66;
	game->plane.y = 0;
}

void	init_south(t_game_info *game)
{
	game->view_dir.x = 0;
	game->view_dir.y = -1;
	game->plane.x = -0.66;
	game->plane.y = 0;
}

void	init_east(t_game_info *game)
{
	game->view_dir.x = 1;
	game->view_dir.y = 0;
	game->plane.x = 0;
	game->plane.y = -0.66;
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
	int player_x;
	int player_y;


	player_x = (int)(game->ray.player.x - 0.5);
	player_y = (int)(game->ray.player.y - 0.5);

	(void) player_x;
	(void) player_y;

	if (start_dir == 'N')
		init_north(game);
	else if (start_dir == 'S')
		init_south(game);
	else if (start_dir == 'W')
		init_west(game);
	else if (start_dir == 'E')
		init_east(game);
	// game->map[player_x][player_y] = '0';
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
				init_ray_dir(game, line[i]);
			}
			else
				error_exit("Error: Invalid map.\n");
		}
		i++;
	}

}
