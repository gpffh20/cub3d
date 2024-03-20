/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gykoh <gykoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:19:13 by gykoh             #+#    #+#             */
/*   Updated: 2024/03/20 11:19:14 by gykoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static void	move_to_north(t_game_info *game)
{
	t_point_double	new_pos;

	new_pos.x = game->ray.player.x + game->view_dir.x * MOVE_SPEED;
	new_pos.y = game->ray.player.y + game->view_dir.y * MOVE_SPEED;
	if (!is_wall(game, (int)(new_pos.x + 0.003), (int)(new_pos.y + 0.003)) &&
		!is_wall(game, (int)(new_pos.x - 0.003), (int)(new_pos.y - 0.003)))
	{
		game->ray.player.x = new_pos.x;
		game->ray.player.y = new_pos.y;
	}
}

static void	move_to_south(t_game_info *game)
{
	t_point_double	new_pos;

	new_pos.x = game->ray.player.x - game->view_dir.x * MOVE_SPEED;
	new_pos.y = game->ray.player.y - game->view_dir.y * MOVE_SPEED;
	if (!is_wall(game, (int)(new_pos.x + 0.003), (int)(new_pos.y + 0.003)) &&
		!is_wall(game, (int)(new_pos.x - 0.003), (int)(new_pos.y - 0.003)))
	{
		game->ray.player.x = new_pos.x;
		game->ray.player.y = new_pos.y;
	}
}

static void	move_to_east(t_game_info *game)
{
	t_point_double	new_pos;

	new_pos.x = game->ray.player.x + game->view_dir.y * MOVE_SPEED;
	new_pos.y = game->ray.player.y - game->view_dir.x * MOVE_SPEED;
	if (!is_wall(game, (int)(new_pos.x + 0.003), (int)(new_pos.y + 0.003)) &&
		!is_wall(game, (int)(new_pos.x - 0.003), (int)(new_pos.y - 0.003)))
	{
		game->ray.player.x = new_pos.x;
		game->ray.player.y = new_pos.y;
	}
}

static void	move_to_west(t_game_info *game)
{
	t_point_double	new_pos;

	new_pos.x = game->ray.player.x - game->view_dir.y * MOVE_SPEED;
	new_pos.y = game->ray.player.y + game->view_dir.x * MOVE_SPEED;
	if (!is_wall(game, (int)(new_pos.x + 0.003), (int)(new_pos.y + 0.003)) &&
		!is_wall(game, (int)(new_pos.x - 0.003), (int)(new_pos.y - 0.003)))
	{
		game->ray.player.x = new_pos.x;
		game->ray.player.y = new_pos.y;
	}
}

void	move_player(t_game_info *game)
{
	if (game->move_flag.no == TRUE)
		move_to_north(game);
	else if (game->move_flag.so == TRUE)
		move_to_south(game);
	else if (game->move_flag.ea == TRUE)
		move_to_east(game);
	else if (game->move_flag.we == TRUE)
		move_to_west(game);
}
