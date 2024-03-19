#include "../../include/cub3D.h"

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