#include "../../include/cub3D.h"

void	my_mlx_pixel_put(t_texture *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}


void	paint_background(t_game_info *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < SCREEN_HEIGHT / 2)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			my_mlx_pixel_put(&game->window, x, y, game->ceiling_color);
			x++;
		}
		y++;
	}
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			my_mlx_pixel_put(&game->window, x, y, game->floor_color);
			x++;
		}
		y++;
	}
}

void	init_vectors(t_raycast *ray, t_game_info *game)
{
	if (ray->ray_dir.x < 0)
	{
		ray->step_dir.x = -1;
		ray->side_dist.x = (game->ray.player.x - ray->player_pos.x) * ray->delta_dist.x;
	}
	else
	{
		ray->step_dir.x = 1;
		ray->side_dist.x = (ray->player_pos.x + 1.0 - game->ray.player.x) * ray->delta_dist.x;
	}
	if (ray->ray_dir.y < 0)
	{
		ray->step_dir.y = -1;
		ray->side_dist.y = (game->ray.player.y - ray->player_pos.y) * ray->delta_dist.y;
	}
	else
	{
		ray->step_dir.y = 1;
		ray->side_dist.y = (ray->player_pos.y + 1.0 - game->ray.player.y) * ray->delta_dist.y;
	}
}

void	dda(t_game_info *game, t_raycast *ray)
{
	int hit_flag;

	hit_flag = 0;
	while (hit_flag == 0)
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side = HOR_LINE;
			ray->side_dist.x += ray->delta_dist.x;
			ray->player_pos.x += ray->step_dir.x;
		}
		else
		{
			ray->side = VER_LINE;
			ray->side_dist.y += ray->delta_dist.y;
			ray->player_pos.y += ray->step_dir.y;
		}
		if (game->map[ray->player_pos.y][ray->player_pos.x] != '0')
			hit_flag = 1;
	}
}

void	calc_wall_length(t_game_info *game, t_raycast *ray)
{
	if (ray->side == VER_LINE)
	{
		game->perp_wall_dist = ray->side_dist.y - ray->delta_dist.y;
		ray->hit_ratio = ray->player.x + game->perp_wall_dist * ray->ray_dir.x;
		if (ray->ray_dir.y < 0)
			ray->hit_ratio = 1 - ray->hit_ratio;
	}
	else
	{
		game->perp_wall_dist = ray->side_dist.x - ray->delta_dist.x;
		ray->hit_ratio = ray->player.y + game->perp_wall_dist * ray->ray_dir.y;
		if (ray->ray_dir.x > 0)
			ray->hit_ratio = 1 - ray->hit_ratio;
	}
	ray->hit_ratio -= floor(ray->hit_ratio);
	ray->line_height = (int)(SCREEN_HEIGHT / game->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + SCREEN_HEIGHT / 2;
	ray->draw_end = ray->line_height / 2 + SCREEN_HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	if (ray->draw_end >= SCREEN_HEIGHT)
		ray->draw_end = SCREEN_HEIGHT - 1;
}

// jj's logic start
void choose_texture(t_game_info *game, t_raycast *ray)
{
	if (ray->side == HOR_LINE && ray->ray_dir.x > 0)
		ray->wall_type = &game->ea_texture;
	else if (ray->side == HOR_LINE && ray->ray_dir.x < 0)
		ray->wall_type = &game->we_texture;
	else if (ray->side == VER_LINE && ray->ray_dir.y < 0)
		ray->wall_type = &game->so_texture;
	else if (ray->side == VER_LINE && ray->ray_dir.y > 0)
		ray->wall_type = &game->no_texture;
}

int	mapping_int(int num, int in_max, int out_max)
{
	return (num * out_max / in_max);
}

int	get_color_in_texture(t_texture *component, int x, int y)
{
	int	res;
	int	*addr_ptr;

	addr_ptr = (int *)component->addr;
	if (x >= component->width || y >= component->height
		|| x < 0 || y < 0)
	{
		return (0);
	}
	res = addr_ptr[component->line_length / (component->bpp / 8) * y + x];
	if (res == -16777216)
	{
		return (0);
	}
	return (res);
}

void wall_in_range(t_game_info *game, int monitor)
{
	int		i;
	int 	y;
	int		color;
	t_point_int	texture_pixel;
	t_texture	*using_image;

	i = 0;
	y = (SCREEN_HEIGHT / 2) - (game->ray.line_height / 2);
	using_image = game->ray.wall_type;
	while (i < game->ray.line_height)
	{
		texture_pixel.x = game->ray.hit_ratio * using_image->width;
		texture_pixel.y = mapping_int(i, game->ray.line_height, using_image->height);
		color = get_color_in_texture(using_image,
				texture_pixel.x, texture_pixel.y);
		my_mlx_pixel_put(&game->window, monitor, y + i, color);
		i++;
	}
}

void wall_out_range(t_game_info *game, int monitor)
{
	int i;
	int color;
	t_point_int texture_pixel;
	t_texture *using_image;

	i = 0;
	using_image = game->ray.wall_type;
	while (i < SCREEN_HEIGHT)
	{
		texture_pixel.x = game->ray.hit_ratio * using_image->width;
		texture_pixel.y = mapping_int(i + (game->ray.line_height / 2 - SCREEN_HEIGHT / 2),
				game->ray.line_height, using_image->height);
		color = get_color_in_texture(using_image,
				texture_pixel.x, texture_pixel.y);
		my_mlx_pixel_put(&game->window, monitor, i, color);
		i++;
	}
}
// jj's logic end

int	draw_map(t_game_info *game)
{
	int monitor;

	monitor = 0;
//	ft_memset(&game->ray, 0, sizeof(t_raycast));
	// TODO: init_player_by_keycode(game) -> 좌우키로 회전;
	paint_background(game);
	while (monitor < SCREEN_WIDTH)
	{
		calc_ray_params(game, &game->ray, monitor);
		init_vectors(&game->ray, game);
		dda(game, &game->ray);
		calc_wall_length(game, &game->ray);
		choose_texture(game, &game->ray);
		if (game->ray.line_height < SCREEN_HEIGHT)
			wall_in_range(game, monitor);
		else
			wall_out_range(game, monitor);
		monitor++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->window.img, 0, 0);
	return SUCCESS;
}

void calc_ray_params(t_game_info *game, t_raycast *ray, int monitor)
{
	double camera_x;

	camera_x = (2 * monitor / (double)SCREEN_WIDTH) - 1; // (-1, 1)
	ray->ray_dir.x = game->view_dir.x + game->plane.x * camera_x; // 빨간선
	ray->ray_dir.y = game->view_dir.y + game->plane.y * camera_x;
	ray->player_pos.x = (int)game->ray.player.x;
	ray->player_pos.y = (int)game->ray.player.y;
	ray->delta_dist.x = fabs(1 / ray->ray_dir.x);
	ray->delta_dist.y = fabs(1 / ray->ray_dir.y);
}
