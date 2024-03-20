/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press_n_release.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gykoh <gykoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 09:19:58 by gykoh             #+#    #+#             */
/*   Updated: 2024/03/20 09:19:59 by gykoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int	key_press(int keycode, t_game_info *game)
{
	if (keycode == ROTATE_LEFT)
		game->move_flag.l = TRUE;
	else if (keycode == ROTATE_RIGHT)
		game->move_flag.r = TRUE;
	else if (keycode == KEY_W)
		game->move_flag.no = TRUE;
	else if (keycode == KEY_S)
		game->move_flag.so = TRUE;
	else if (keycode == KEY_D)
		game->move_flag.ea = TRUE;
	else if (keycode == KEY_A)
		game->move_flag.we = TRUE;
	else if (keycode == ESC)
		exit_game(game);
	return (SUCCESS);
}

int	key_release(int keycode, t_game_info *game)
{
	if (keycode == ROTATE_LEFT)
		game->move_flag.l = FALSE;
	else if (keycode == ROTATE_RIGHT)
		game->move_flag.r = FALSE;
	else if (keycode == KEY_W)
		game->move_flag.no = FALSE;
	else if (keycode == KEY_S)
		game->move_flag.so = FALSE;
	else if (keycode == KEY_D)
		game->move_flag.ea = FALSE;
	else if (keycode == KEY_A)
		game->move_flag.we = FALSE;
	return (SUCCESS);
}
