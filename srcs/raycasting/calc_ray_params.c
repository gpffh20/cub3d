#include "../../include/cub3D.h"

void calc_ray_params(t_game_info *game, t_raycast *ray, int monitor)
{
	double camera_x;

	camera_x = (2 * monitor / (double)SCREEN_WIDTH) - 1;
	ray->ray_dir.x = game->view_dir.x + game->plane.x * camera_x;
	ray->ray_dir.y = game->view_dir.y + game->plane.y * camera_x;
	ray->player_pos.x = (int)game->ray.player.x;
	ray->player_pos.y = (int)game->ray.player.y;
	ray->delta_dist.x = fabs(1 / ray->ray_dir.x);
	ray->delta_dist.y = fabs(1 / ray->ray_dir.y);
}