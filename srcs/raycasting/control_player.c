/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gykoh <gykoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 09:19:33 by gykoh             #+#    #+#             */
/*   Updated: 2024/03/20 09:19:34 by gykoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	control_player(t_game_info *game)
{
	if (game->move_flag.no == TRUE || game->move_flag.so == TRUE \
		|| game->move_flag.ea == TRUE || game->move_flag.we == TRUE)
		move_player(game);
	else if (game->move_flag.r == TRUE || game->move_flag.l == TRUE)
		rotate_player(game);
}
