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

int	exit_game(t_game_info *game)
{
	mlx_destroy_window(game->mlx, game->win);
	exit(0);
	return (0);
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
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D");
	draw_map(&game);
	// draw_map(&game);
	// mlx_hook(game.win, KEY_PRESS, 0, &key_press, &game);
	// mlx_hook(game.win, KEY_RELEASE, 0, &key_release, &game);
	// mlx_key_hook(game.win, &exit_game, &game);
	mlx_loop(game.mlx);
	
	return (0);
}
