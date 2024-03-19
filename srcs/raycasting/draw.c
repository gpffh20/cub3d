#include "../../include/cub3D.h"

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
	if (x < 1 || y < 1 || x > game->map_width - 1 || y > game->map_height - 1)
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
	if (!is_wall(game, (int)(new_pos.x + 0.003), (int)(new_pos.y + 0.003)) &&
		!is_wall(game, (int)(new_pos.x - 0.003), (int)(new_pos.y - 0.003)))
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
	if (!is_wall(game, (int)(new_pos.x + 0.003), (int)(new_pos.y + 0.003)) &&
		!is_wall(game, (int)(new_pos.x - 0.003), (int)(new_pos.y - 0.003)))
	{
		game->ray.player.x = new_pos.x;
		game->ray.player.y = new_pos.y;
	}
}

void move_to_east(t_game_info *game)
{
	t_point_double new_pos;

	new_pos.x = game->ray.player.x + game->view_dir.y * MOVE_SPEED;		// +
	new_pos.y = game->ray.player.y - game->view_dir.x * MOVE_SPEED;
	if (!is_wall(game, (int)(new_pos.x + 0.003), (int)(new_pos.y + 0.003)) &&
		!is_wall(game, (int)(new_pos.x - 0.003), (int)(new_pos.y - 0.003)))
	{
		game->ray.player.x = new_pos.x;
		game->ray.player.y = new_pos.y;
	}
}

void move_to_west(t_game_info *game)
{
	t_point_double new_pos;

	new_pos.x = game->ray.player.x - game->view_dir.y * MOVE_SPEED;		// -
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

void rotate_to_right(t_game_info *game)	// 아직 안건듦
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

void rotate_to_left(t_game_info *game)
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
		rotate_to_right(game);
	else if (game->move_flag.l == TRUE)
		rotate_to_left(game);
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
	control_player(game);
	while (monitor < SCREEN_WIDTH)
	{
		calc_ray_params(game, &game->ray, monitor);
		init_vectors(&game->ray, game);
		dda(game, &game->ray);
		choose_texture(game, &game->ray);
		calc_wall_length(game, &game->ray);
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
