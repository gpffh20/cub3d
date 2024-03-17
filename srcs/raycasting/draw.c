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

// void	dda(t_game_info *game, t_raycast *ray)
// {
// 	int hit_flag;

// 	hit_flag = 0;
// 	while (hit_flag == 0)
// 	{
// 		if (ray->side_dist.x < ray->side_dist.y)
// 		{
// 			ray->side_dist.x += ray->delta_dist.x;
// 			ray->player_pos.x += ray->step_dir.x;
// 			ray->side = 0;
// 		}
// 		else
// 		{
// 			ray->side_dist.y += ray->delta_dist.y;
// 			ray->player_pos.y += ray->step_dir.y;
// 			ray->side = 1;
// 		}
// 		if (game->map[ray->player_pos.y][ray->player_pos.x] == '1')
// 			hit_flag = 1;
// 	}
// }

void	draw_map(t_game_info *game)
{
	int monitor;

	monitor = 0;
	paint_background(game);
	while (monitor < SCREEN_WIDTH)
	{
		calc_ray_params(game, &game->ray, monitor);
		init_vectors(&game->ray, game);
		// TODO: dda 알고리즘 구현
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
	// TODO: side_dist 초기화는 dda에서 하기
}
