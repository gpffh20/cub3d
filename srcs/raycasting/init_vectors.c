#include "../../include/cub3D.h"

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