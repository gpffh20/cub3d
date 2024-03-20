/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gykoh <gykoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 09:18:35 by gykoh             #+#    #+#             */
/*   Updated: 2024/03/20 09:18:36 by gykoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	fill_map(char *line, t_game_info *game)
{
	int	i;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (line[i] == '1' || line[i] == '0')
	{
		game->map_start++;
		if (game->map_start - 1 == 0)
			check_map_valid(line, game, SIDE_FIRST);
		else if (game->map_start == game->map_height)
			check_map_valid(line, game, SIDE_LAST);
		else
			check_map_valid(line, game, MIDDLE);
	}
}
