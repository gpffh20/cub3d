#include "../include/cub3D.h"

int	main(int ac, char **av)
{
	t_game_info	game;

	if (ac != 2)
		error_exit("Error: Wrong number of arguments.\n");
	invalid_file(av[1]);
	init_game(&game);
	get_info(av[1], &game);
	get_map(av[1], &game);
	init_texture(&game);
	init_move_flag(&game);
	mlx_hook(game.win, KEY_PRESS, 0, &key_press, &game);
	mlx_hook(game.win, KEY_RELEASE, 0, &key_release, &game);
	mlx_hook(game.win, ESC, 0, &exit_game, &game);
	mlx_hook(game.win, CLICK_CLOSE, 0, &exit_game, &game);
	mlx_loop_hook(game.mlx, &draw_map, &game);
	mlx_loop(game.mlx);
	return (0);
}
