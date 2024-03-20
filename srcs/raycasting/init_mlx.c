/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gykoh <gykoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 09:19:49 by gykoh             #+#    #+#             */
/*   Updated: 2024/03/20 11:18:51 by gykoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static void	init_texture(t_game_info *game)
{
	game->no_texture.img = mlx_xpm_file_to_image(game->mlx, \
			game->no_path, &game->no_texture.width, \
			&game->no_texture.height);
	game->no_texture.addr = mlx_get_data_addr(game->no_texture.img, \
			&game->no_texture.bpp, &game->no_texture.line_length, \
			&game->no_texture.endian);
	game->so_texture.img = mlx_xpm_file_to_image(game->mlx, \
			game->so_path, &game->so_texture.width, \
			&game->so_texture.height);
	game->so_texture.addr = mlx_get_data_addr(game->so_texture.img, \
			&game->so_texture.bpp, &game->so_texture.line_length, \
			&game->so_texture.endian);
	game->we_texture.img = mlx_xpm_file_to_image(game->mlx, \
			game->we_path, &game->we_texture.width, \
			&game->we_texture.height);
	game->we_texture.addr = mlx_get_data_addr(game->we_texture.img, \
			&game->we_texture.bpp, &game->we_texture.line_length, \
			&game->we_texture.endian);
	game->ea_texture.img = mlx_xpm_file_to_image(game->mlx, \
			game->ea_path, &game->ea_texture.width, \
			&game->ea_texture.height);
	game->ea_texture.addr = mlx_get_data_addr(game->ea_texture.img, \
			&game->ea_texture.bpp, &game->ea_texture.line_length, \
			&game->ea_texture.endian);
}

void	init_mlx(t_game_info *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D");
	game->window.img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	game->window.addr = mlx_get_data_addr(game->window.img, \
			&game->window.bpp, &game->window.line_length, &game->window.endian);
	init_texture(game);
	mlx_put_image_to_window(game->mlx, game->win, game->window.img, 0, 0);
}
