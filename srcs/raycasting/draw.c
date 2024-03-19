#include "../../include/cub3D.h"

void	mlx_pixel_put_once(t_texture *img, int x, int y, int color)
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
			mlx_pixel_put_once(&game->window, x, y, game->ceiling_color);
			x++;
		}
		y++;
	}
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			mlx_pixel_put_once(&game->window, x, y, game->floor_color);
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
		ray->side_dist.x = (ray->player_pos.x + 1 - game->ray.player.x) * ray->delta_dist.x;
	}
	if (ray->ray_dir.y < 0)
	{
		ray->step_dir.y = -1; // 되돌림
		ray->side_dist.y = (game->ray.player.y - ray->player_pos.y) * ray->delta_dist.y;
	}
	else
	{
		ray->step_dir.y = 1; // 되돌림
		ray->side_dist.y = (ray->player_pos.y + 1 - game->ray.player.y) * ray->delta_dist.y;
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

void choose_texture(t_game_info *game, t_raycast *ray)
{
	if (ray->side == VER_LINE && ray->ray_dir.y > 0)
		ray->wall_type = &game->no_texture;
	else if (ray->side == VER_LINE && ray->ray_dir.y < 0)
		ray->wall_type = &game->so_texture;
	else if (ray->side == HOR_LINE && ray->ray_dir.x > 0)
		ray->wall_type = &game->ea_texture;
	else if (ray->side == HOR_LINE && ray->ray_dir.x < 0)
		ray->wall_type = &game->we_texture;
}

int	fetch_pixel_color(t_texture *texture, int x, int y)
{
	int	res;
	int	*texture_addr;

	texture_addr = (int *)texture->addr;
	if (x >= texture->width || y >= texture->height
		|| x < 0 || y < 0)
		return (0);
	res = texture_addr[texture->line_length / (texture->bpp / 8) * y + x];
	return (res);
}

void draw_texture_default(t_game_info *game, int monitor)
{
	t_point_int	texture_pixel;
	t_texture		*type_texture;
	int					texture_y_idx;
	int 				screen_y_pos;
	int					color;

	texture_y_idx = 0;
	screen_y_pos = (SCREEN_HEIGHT / 2) - (game->ray.line_height / 2);
	type_texture = game->ray.wall_type;
	while (texture_y_idx < game->ray.line_height)
	{
		texture_pixel.x = game->ray.hit_ratio * type_texture->width;
		texture_pixel.y = texture_y_idx * type_texture->height / game->ray.line_height;
		color = fetch_pixel_color(type_texture, texture_pixel.x, texture_pixel.y);
		mlx_pixel_put_once(&game->window, monitor, screen_y_pos + texture_y_idx, color);
		texture_y_idx++;
	}
}

void draw_texture_close(t_game_info *game, int monitor)
{
	int texture_y_idx;
	int color;
	t_point_int texture_pixel;
	t_texture *type_texture;

	texture_y_idx = 0;
	type_texture = game->ray.wall_type;
	while (texture_y_idx < SCREEN_HEIGHT)
	{
		texture_pixel.x = game->ray.hit_ratio * type_texture->width;
		texture_pixel.y = (texture_y_idx + (game->ray.line_height / 2 - SCREEN_HEIGHT / 2))
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

int is_wall(t_game_info *game, int x, int y)
{
	if (x < 0 || y < 0 || x >= game->map_width || y >= game->map_height)
		return (TRUE);
	if (game->map[y][(int)game->ray.player.x] == '0' &&
		game->map[(int)game->ray.player.y][x] == '0')
		return (FALSE);
	return (TRUE);
}

void move_to_north(t_game_info *game)
{
	t_point_double new_pos;

	new_pos.x = game->ray.player.x + game->view_dir.x * MOVE_SPEED;
	new_pos.y = game->ray.player.y + game->view_dir.y * MOVE_SPEED;
	if (!is_wall(game, (int)new_pos.x, (int)new_pos.y))
	{
		game->ray.player.x = new_pos.x;
		game->ray.player.y = new_pos.y;
	}
}

void move_to_south(t_game_info *game)
{
	t_point_double new_pos;

	new_pos.x = game->ray.player.x - game->view_dir.x * MOVE_SPEED;
	new_pos.y = game->ray.player.y - game->view_dir.y * MOVE_SPEED;
	if (!is_wall(game, (int)new_pos.x, (int)new_pos.y))
	{
		game->ray.player.x = new_pos.x;
		game->ray.player.y = new_pos.y;
	}
}

void move_to_east(t_game_info *game)
{
	t_point_double new_pos;

	new_pos.x = game->ray.player.x + game->view_dir.x * MOVE_SPEED;
	new_pos.y = game->ray.player.y - game->view_dir.y * MOVE_SPEED;
	if (!is_wall(game, (int)new_pos.x, (int)new_pos.y))
	{
		game->ray.player.x = new_pos.x;
		game->ray.player.y = new_pos.y;
	}
}

void move_to_west(t_game_info *game)
{
	t_point_double new_pos;

	new_pos.x = game->ray.player.x - game->view_dir.x * MOVE_SPEED;
	new_pos.y = game->ray.player.y + game->view_dir.y * MOVE_SPEED;
	if (!is_wall(game, (int)new_pos.x, (int)new_pos.y))
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

void ratate_to_right(t_game_info *game)
{
	t_point_double old_dir;
	t_point_double old_plane;
	double	rad;

	rad = asin(tan(M_PI / 6)) * (-ROTATE_SPEED);
	old_dir.x = game->view_dir.x;
	old_dir.y = game->view_dir.y;
	old_plane.x = game->plane.x;
	old_plane.y = game->plane.y;
	game->view_dir.x = old_dir.x * cos(rad) - old_dir.y * sin(rad);
	game->view_dir.y = old_dir.x * sin(rad) + old_dir.y * cos(rad);
	game->plane.x = old_plane.x * cos(rad) - old_plane.y * sin(rad);
	game->plane.y = old_plane.x * sin(rad) + old_plane.y * cos(rad);
}

void ratate_to_left(t_game_info *game)
{
	t_point_double old_dir;
	t_point_double old_plane;
	double	rad;

	rad = asin(tan(M_PI / 6)) * ROTATE_SPEED;
	old_dir.x = game->view_dir.x;
	old_dir.y = game->view_dir.y;
	old_plane.x = game->plane.x;
	old_plane.y = game->plane.y;
	game->view_dir.x = old_dir.x * cos(rad) - old_dir.y * sin(rad);
	game->view_dir.y = old_dir.x * sin(rad) + old_dir.y * cos(rad);
	game->plane.x = old_plane.x * cos(rad) - old_plane.y * sin(rad);
	game->plane.y = old_plane.x * sin(rad) + old_plane.y * cos(rad);
}

void rotate_player(t_game_info *game)
{
	if (game->move_flag.r == TRUE)
		ratate_to_right(game);
	else if (game->move_flag.l == TRUE)
		ratate_to_left(game);
}

void	control_player(t_game_info *game)
{
	if (game->move_flag.no == TRUE || game->move_flag.so == TRUE || game->move_flag.ea == TRUE || game->move_flag.we == TRUE)
		move_player(game);
	else if (game->move_flag.r == TRUE || game->move_flag.l == TRUE)
		rotate_player(game);
}

int	draw_map(t_game_info *game)
{
	int monitor;

	monitor = 0;
	paint_background(game);
	control_player(game); // key 별 움직이는거 구현한 부분
	while (monitor < SCREEN_WIDTH)
	{
		calc_ray_params(game, &game->ray, monitor);
		init_vectors(&game->ray, game);
		dda(game, &game->ray);
		calc_wall_length(game, &game->ray);
		choose_texture(game, &game->ray);
		draw_texture(game, monitor);
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
