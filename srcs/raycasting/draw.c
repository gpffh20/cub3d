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

void	draw_map(t_game_info *game)
{
	int monitor;

	monitor = 0;
	paint_background(game);
	while (monitor < SCREEN_WIDTH)
	{
		calc_ray_params(game, &game->ray, monitor);
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
