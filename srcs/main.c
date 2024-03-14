#include "../include/cub3D.h"

void	init_game(t_game_info *game)
{
	game->no_path = NULL;
	game->so_path = NULL;
	game->we_path = NULL;
	game->ea_path = NULL;
	game->floor_color = -1;
	game->ceiling_color = -1;
	game->start_x = 0;
	game->start_y = 0;
	game->map = NULL;
	game->map_width = 0;
	game->map_height = 0;
	game->player_cnt = 0;
	game->map_start = 0;
}

int main(int ac, char **av)
{
	t_game_info game;

	if (ac != 2)
		error_exit("Error: Wrong number of arguments.\n");
	invalid_file(av[1]);
	init_game(&game);
	get_info(av[1], &game);
	get_map(av[1], &game);
	return (0);
}
