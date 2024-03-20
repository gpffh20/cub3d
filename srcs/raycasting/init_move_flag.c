/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_move_flag.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gykoh <gykoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 09:19:51 by gykoh             #+#    #+#             */
/*   Updated: 2024/03/20 09:19:52 by gykoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	init_move_flag(t_game_info *game)
{
	game->move_flag.l = FALSE;
	game->move_flag.r = FALSE;
	game->move_flag.no = FALSE;
	game->move_flag.so = FALSE;
	game->move_flag.ea = FALSE;
	game->move_flag.we = FALSE;
}
