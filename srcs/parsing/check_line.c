/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gykoh <gykoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 09:18:12 by gykoh             #+#    #+#             */
/*   Updated: 2024/03/20 11:58:32 by gykoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	check_line(char *line, t_game_info *game)
{
	int	i;

	if (line[ft_strlen(line)-2] == '0')
		error_exit("Error: Invalid map.\n");
	if (!ft_strncmp("NO ", line, 3) || !ft_strncmp("SO ", line, 3)
		|| !ft_strncmp("WE ", line, 3) || !ft_strncmp("EA ", line, 3))
		get_path(line[0], line, game);
	else if (!ft_strncmp("C ", line, 2) || !ft_strncmp("F ", line, 2))
		get_color(line[0], line + 2, game);
	if (game->map_start == 1 && line[0] == '\n')
		error_exit("Error: Invalid map.\n");
	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	if (line[i] == '1' || line[i] == '0')
	{
		game->map_start = 1;
		if (!game->no_path || !game->so_path || !game->we_path || !game->ea_path
			|| game->ceiling_color == -1 || game->floor_color == -1)
			error_exit("Error: Missing information.\n");
		check_map(line, game);
		game->map_height++;
		game->map_width = ft_max(game->map_width, ft_strlen(line));
	}
}
