/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gykoh <gykoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 09:20:05 by gykoh             #+#    #+#             */
/*   Updated: 2024/03/20 11:08:06 by gykoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	init_mlx(&game);
	init_move_flag(&game);
	mlx_hook(game.win, KEY_PRESS, 0, &key_press, &game);
	mlx_hook(game.win, KEY_RELEASE, 0, &key_release, &game);
	mlx_hook(game.win, CLICK_CLOSE, 0, &exit_game, &game);
	mlx_loop_hook(game.mlx, &draw_map, &game);
	mlx_loop(game.mlx);
	return (0);
}
