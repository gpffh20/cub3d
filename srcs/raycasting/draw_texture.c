/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gykoh <gykoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 09:19:38 by gykoh             #+#    #+#             */
/*   Updated: 2024/03/20 09:19:39 by gykoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static void	draw_texture_default(t_game_info *game, int monitor)
{
	t_point_int	texture_pixel;
	t_texture	*type_texture;
	int			texture_y_idx;
	int			screen_y_pos;
	int			color;

	texture_y_idx = 0;
	screen_y_pos = (SCREEN_HEIGHT / 2) - (game->ray.line_height / 2);
	type_texture = game->ray.wall_type;
	while (texture_y_idx < game->ray.line_height)
	{
		texture_pixel.x = game->ray.hit_ratio * type_texture->width;
		texture_pixel.y = texture_y_idx * type_texture->height \
						/ game->ray.line_height;
		color = fetch_pixel_color(type_texture, texture_pixel.x, \
									texture_pixel.y);
		mlx_pixel_put_once(&game->window, monitor, \
							screen_y_pos + texture_y_idx, color);
		texture_y_idx++;
	}
}

static void	draw_texture_close(t_game_info *game, int monitor)
{
	int			texture_y_idx;
	int			color;
	t_point_int	texture_pixel;
	t_texture	*type_texture;

	texture_y_idx = 0;
	type_texture = game->ray.wall_type;
	while (texture_y_idx < SCREEN_HEIGHT)
	{
		texture_pixel.x = game->ray.hit_ratio * type_texture->width;
		texture_pixel.y = (texture_y_idx + \
						(game->ray.line_height / 2 - SCREEN_HEIGHT / 2)) \
						* type_texture->height / game->ray.line_height;
		color = fetch_pixel_color(type_texture,
				texture_pixel.x, texture_pixel.y);
		mlx_pixel_put_once(&game->window, monitor, texture_y_idx, color);
		texture_y_idx++;
	}
}

void	draw_texture(t_game_info *game, int monitor)
{
	if (game->ray.line_height < SCREEN_HEIGHT)
		draw_texture_default(game, monitor);
	else
		draw_texture_close(game, monitor);
}
