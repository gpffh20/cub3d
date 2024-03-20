/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_valid.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gykoh <gykoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 09:18:15 by gykoh             #+#    #+#             */
/*   Updated: 2024/03/20 09:18:16 by gykoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static void	check_side_first(char *line, t_game_info *game)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != ' ' && line[i] != '\n')
			error_exit("Error: Invalid map.\n");
		game->map[game->map_start - 1][i] = line[i];
		i++;
	}
	while (i < game->map_width)
	{
		game->map[game->map_start - 1][i] = ' ';
		i++;
	}
}

static void	check_side_last(char *line, t_game_info *game)
{
	int	i;

	i = 0;
	while (line[i])
	{
		deep_check(game, line, i);
		if (line[i] != '1' && line[i] != ' ' && line[i] != '\n')
			error_exit("Error: Invalid map.\n");
		game->map[game->map_start - 1][i] = line[i];
		if (line[i] == ' ' && game->map[game->map_start - 2][i] == '0')
			error_exit("Error: Invalid map.\n");
		i++;
	}
	while (i < game->map_width)
	{
		game->map[game->map_start - 1][i] = ' ';
		if (line[i] == ' ' && game->map[game->map_start - 2][i] == '0')
			error_exit("Error: Invalid map.\n");
		i++;
	}
}

static void	check_middle(char *line, t_game_info *game)
{
	int	i;

	i = 0;
	while (line[i])
	{
		deep_check(game, line, i);
		game->map[game->map_start - 1][i] = line[i];
		if (line[i] == 'N' || line[i] == 'S' || line[i] == 'W'
			|| line[i] == 'E')
		{
			init_ray_dir(game, line[i]);
			game->map[game->map_start - 1][i] = '0';
		}
		i++;
	}
	while (i < game->map_width)
	{
		game->map[game->map_start - 1][i] = ' ';
		i++;
	}
}

void	check_map_valid(char *line, t_game_info *game, int type)
{
	if (type == SIDE_FIRST)
		check_side_first(line, game);
	else if (type == SIDE_LAST)
		check_side_last(line, game);
	else if (type == MIDDLE)
		check_middle(line, game);
}
