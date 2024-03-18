#include "../../include/cub3D.h"

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
			mlx_pixel_put(game->mlx, game->win, x, y, game->ceiling_color);
			x++;
		}
		y++;
	}
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			mlx_pixel_put(game->mlx, game->win, x, y, game->floor_color);
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
		if (game->map[ray->player_pos.y][ray->player_pos.x] == '1')
			hit_flag = 1;
	}
}

void	calc_wall_length(t_game_info *game, t_raycast *ray)
{
	if (ray->side == VER_LINE)
	{
		game->perp_wall_dist = (ray->player_pos.x - game->ray.player.x + (1 - ray->step_dir.x) / 2) / ray->ray_dir.x;
		ray->hit_ratio = ray->player.x + game->perp_wall_dist * ray->ray_dir.x;
	}
	else
	{
		game->perp_wall_dist = (ray->player_pos.y - game->ray.player.y + (1 - ray->step_dir.y) / 2) / ray->ray_dir.y;
		ray->hit_ratio = ray->player.y + game->perp_wall_dist * ray->ray_dir.y;
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

void	draw_map(t_game_info *game)
{
	int monitor;

	monitor = 0;
	init_texture(game);
	paint_background(game);
	while (monitor < SCREEN_WIDTH)
	{
		calc_ray_params(game, &game->ray, monitor);
		init_vectors(&game->ray, game);
		dda(game, &game->ray);
		calc_wall_length(game, &game->ray);
		// TODO: 부딛힌 벽 방향, 좌표 기준으로 mlx 값 저장해둬야함

	// 구조체 값 확인 코드
	// printf("Monitor: %d\n", monitor);
	// printf("Ray Direction: (%f, %f)\n", game->ray.ray_dir.x, game->ray.ray_dir.y);
	// printf("Delta Distance: (%f, %f)\n", game->ray.delta_dist.x, game->ray.delta_dist.y);
	// printf("Side Distance: (%f, %f)\n", game->ray.side_dist.x, game->ray.side_dist.y);
	// printf("Player Position: (%f, %f)\n", game->ray.player.x, game->ray.player.y);
	// printf("Player Map Position: (%d, %d)\n", game->ray.player_pos.x, game->ray.player_pos.y);
	// printf("Step Direction: (%d, %d)\n", game->ray.step_dir.x, game->ray.step_dir.y);
	// printf("Side: %d\n", game->ray.side);
	// printf("Line Height: %d\n", game->ray.line_height);
	// printf("Draw Start: %d, Draw End: %d\n", game->ray.draw_start, game->ray.draw_end);
	// printf("Hit Ratio: %d\n\n", game->ray.hit_ratio);
	// printf("draw_start: %d, draw_end: %d\n", game->ray.draw_start, game->ray.draw_end);
		monitor++;
	}
	return ;
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
